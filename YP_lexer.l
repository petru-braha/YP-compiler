%{
    #include <stdio.h>
    #include "YP_parser.tab.hpp"
%}

/* lexical description - regex */
reserved_type "int"|"float"|"char"|"string"|"bool"
type_array (\[([1-9][0-9]*)\])*

something_name [a-zA-Z_][a-zA-Z0-9_]*
constant_int 0|-[1-9][0-9]*|[1-9][0-9]*
constant_flt {constant_int}.[0-9]+
constant_chr \'[^']\'
constant_str \"[^"]+\"
constant_bol "true"|"false"

%option noyywrap

%%
"master()" { yylval.token_name = strdup(yytext); 
    return MASTER; }

"class" { yylval.token_name = strdup(yytext); 
    return R_CLS; }

{reserved_type}{type_array} { yylval.token_name = strdup(yytext); 
    return R_TYP; }

"if"|"for"|"while" { yylval.token_name = strdup(yytext); 
    return R_SEQ; }

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

"<-"|"=" { yylval.token_name = strdup(yytext);
    return OPERATOR_ASSIGN; }
"<"|">"|"<="|">="|"!="|"=="|"===" { yylval.token_name = strdup(yytext);
    return OPERATOR_RELTIN; }

[ \t\r] ;
\n {yylineno++;}
. {return yytext[0];}
