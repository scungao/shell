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

extern converter woods;

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
%token EOL

%type <cstr> SYM
%type <nat> NUM command
%type <tree> term 

%left ADD SUB
%left MUL DIV
%left EXP SIN COS TAN LOG
//%nonassoc UMINUS

%start  script

%%

script: command_list
  ;

command_list: command EOL
  | command_list command EOL
  ;

term: SYM
  | NUM { 
    string s = to_string($1);
    cout<<s;

    ast* = new ast;
    woods->num("1");

    $$ = $1;

  }
  | term ADD term
  | term SUB term
  | term MUL term
  | term DIV term
  | SIN '(' term ')'
  | COS '(' term ')'
  | '(' term ')'
  ;

command: 
  | EOL {
    return 0;
  }
  ;

/*
command: var_decl
  | assignment
  | action
  ;

assignment: lval CEQ term 
  ;

lval: var
  | label
  ;

atom: TOP
  | BOT
  | term EQ term
  | term GT term
  | term LT term
  | term LEQ term
  | term GEQ term
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