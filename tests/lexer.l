%{
#include <stdlib.h>
#include <stdio.h>
#include "parse.tab.hpp"

void yyerror(const char * s);
bool master_started = false;

%}

/* lexical description - regex */
reserved_type "int"|"float"|"char"|"string"|"bool"
type_array (\[([1-9][0-9]*)\])*

something_name [a-zA-Z_][a-zA-Z0-9_]*
constant_int 0|-[1-9][0-9]*|[1-9][0-9]*
constant_flt {constant_int}.[0-9]+
constant_chr \'[^\']\'
constant_str \"[^\"]+\"
constant_bol "true"|"false"

comment #.*

%option noyywrap

%%

{reserved_type}{type_array} { yylval.token_name = strdup(yytext);
    return R_TYP; }

{constant_int} { yylval.token_name = strdup(yytext);
    return C_INT; }
{constant_flt} { yylval.token_name = strdup(yytext);
    return C_FLT; }
{constant_chr} { yylval.token_name = strdup(yytext);
    return C_CHR; }
{constant_str} { yylval.token_name = strdup(yytext);
    return C_STR; }
{constant_bol} { yylval.token_name = strdup(yytext);
    return C_BOL; }

{something_name} { yylval.token_name = strdup(yytext); 
    return S_NME; }


"+"|"-" { yylval.token_name = strdup(yytext);
    return OP0; }
"*"|"/"|"^" { yylval.token_name = strdup(yytext);
    return OP1; }
"%" { yylval.token_name = strdup(yytext);
    return OP2; }
"=="|"!="|"&&"|"||"|">="|"<="|">"|"<" { yylval.token_name = strdup(yytext);
    return OP3; }

{comment}

[ \t\r] ;
\n {yylineno++;}
. {return yytext[0];}
