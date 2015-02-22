%{
#include "src/ast.h"
#include "parser.tab.h"
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
"quit" { return QUIT; }
"-"?((([0-9]+)|([0-9]*\.?[0-9]+))([eE][-+]?[0-9]+)?) { yylval.real = atof(yytext); return NUM; }
[a-zA-Z~!@\$\%\^&\*_\-\+=\<\>\.\?\/'][a-zA-Z0-9~!@\$\%\^&\*_\-\+=\<\>\.\?\/']*  { yylval.cstr = strdup(yytext); return SYM; }
\n  { return EOL; }
[ \t]	;
.	{ printf("error: %c\n", *yytext); }
%%