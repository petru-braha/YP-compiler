%{
    #include <stdio.h>
    #include "YP_parser.tab.hpp"
%}

something_name [a-zA-Z_][a-zA-Z0-9_]*

%option noyywrap

%%

"class" { yylval.token_name = strdup(yytext); 
    return R_CLS; }

"int"|"float"|"char"|"string"|"bool" { yylval.token_name = strdup(yytext); 
    return R_TYP; }

{something_name} {yylval.token_name = strdup(yytext); 
    return S_NME;}

"if"|"for"|"while" {yylval.token_name = strdup(yytext); 
    return R_SEQ; }

[ \t] ;
\n {yylineno++;}
. {return yytext[0];}
