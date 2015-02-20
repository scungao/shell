%{
#include "parser.tab.h"
#include "src/ast.h"
#define YY_DECL extern "C" int yylex()

%}
%%
"+"	{ return ADD; }
"-" { return SUB; }
"*" { return MUL; }
"/" { return DIV; }
"sin" { return SIN; }
"cos" { return COS; }
"<" { return LT; }
">" { return GT; }
"=" { return EQ; }
"<=" { return LEQ; }
">=" { return GEQ; }
":=" { return CEQ; }
[0-9]+ { yylval.nat = atoi(yytext); return NUM; } 
[a-zA-Z]+ { yylval.cstr = yytext; return SYM; }
\n  { return EOL; }
[ \t]	;
.	{ printf("error: %c\n", *yytext); }
%%