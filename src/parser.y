%{
#include <iostream>
#include <stdio.h>
#include <string>
#include "src/converter.h"
#include "src/ast.h"

using namespace std;

extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;

extern table* full_table;
extern converter* operators;

void yyerror(const char *s);
%}

%union 
{
  char* cstr;
  double real;
  int nat;
  ast*  tree;
}

/* declare tokens */ 
%token NUM SYM
%token ADD SUB MUL DIV 
%token EQ LEQ GEQ LT GT CEQ
%token AND OR NOT IMP BOT TOP
%token EOL QUIT SOLVE DEF
%token LP LB RP RB COMMA

%type <cstr> SYM QUIT
%type <real> NUM
%type <tree> term atom formula astree BOT TOP

%left IMP
%left OR
%left AND 
%left NOT
%left ADD SUB
%left MUL DIV
%left EXP SIN COS TAN LOG
%left POW
//%nonassoc UMINUS

%start  script

%%

script: command_list
  ;

command_list: command EOL
  | command_list command EOL
  | EOL
  ;

command: declaration 
  | assignment 
  | action
  ;

declaration: LB NUM COMMA NUM RB SYM {
    string s($6);
    ast* a = operators -> var(s);
    a -> set_bounds($2, $4);
  }
  | LB NUM NUM RB SYM {
    string s($5);
    ast* a = operators -> var(s);
    a -> set_bounds($2, $3);
  }
  | LB NUM RB SYM {
    string s($4);
    ast* a = operators -> num($2);
    operators -> mklabel(s, a);
  }
  | DEF SYM NUM {
    string s($2);
    ast* a = operators -> num($3);
    operators -> mklabel(s, a);    
  }
  ;

assignment:
  SYM CEQ astree {
    string s($1);
    operators -> mklabel(s, $3);
  }
  ;

astree: term
  | formula
  ;

action: SOLVE formula
  | SOLVE SYM {
    string s($2);
    ast* a = operators-> find_label(s);
    if (a == NULL) {
      cout<<"Undeclared label.\n";
    }
    else if ( !operators->is_formula(a) ) {
      cout<<"You have to solve a formula.\n";
    }
    else 
      cout<<"solving...\n";
  }
  ;

term: 
  SYM {
    string s($1);
    ast* a = operators -> get_var(s);
    if (a!=NULL) {
      $$ = a;
    }
    else {
      a = operators -> find_label(s);
      if (a!=NULL && operators -> is_term(a))
        $$ = a;
      else
        cout<<"label error\n";
    }
  }
  | NUM {
    $$ = operators->num($1);    
  }
  | term ADD term {
    $$ = operators->add($1, $3);
  }
  | term SUB term {
    $$ = operators->sub($1, $3);
  }
  | term MUL term {
    $$ = operators->mul($1, $3);
  } 
  | term DIV term {
    $$ = operators->div($1, $3);
  }
  | SIN LP term RP {
    $$ = operators->sin($3);
  }
  | COS LP term RP {
    $$ = operators->cos($3);
  }
  | TAN LP term RP {  
    $$ = operators->tan($3);
  }
  | term POW term {
    $$ = operators -> pow($1, $3);
  }
  | LP term RP {
    $$ = $2;
  }
  ;

atom: 
  TOP {
    $$ = operators -> top(); 
  }
  | BOT {
    $$ = operators -> bot();
  }
  | term GT term {
    $$ = operators -> gt($1, $3);    
  }
  | term LT term {
    $$ = operators -> lt($1, $3);    
  }
  | term GEQ term {
    $$ = operators -> geq($1, $3);    
  }
  | term LEQ term {
    $$ = operators -> leq($1, $3);    
  }
  | term EQ term {
   $$ = operators -> eq($1, $3);    
  }
  ;

formula: atom
  | NOT formula {
    $$ = operators -> lnot($2);
  }
  | formula AND formula {
    $$ = operators -> land($1, $3);
  }
  | formula OR formula {
    $$ = operators -> lor($1, $3);
  }
  | formula IMP formula {
    $$ = operators -> limplies($1, $3);
  }
  ;


/*
calclist: 
  | calclist exp EOL 
    { printf("= %d\n", $1); }
  ;

exp: factor
  | exp ADD factor 
    { $$ = $1 + $3; } 
  | exp SUB factor 
    { $$ = $1 - $3; } 
  ;

factor: term 
  | factor MUL term 
    { $$ = $1 * $3; } 
  | factor DIV term 
    { $$ = $1 / $3; } 
  ;

term: NUMBER 
  | ABS term 
    { $$ = $2 >= 0? $2 : - $2; } 
  ;
*/

%%
void yyerror(const char *s) {
  cout << "EEK, parse error!  Message: " << s << endl;
  exit(-1);
}