%{
    #include <stdio.h>
    #include "YP_parser.tab.hpp"
%}

something_name [a-zA-Z_][a-zA-Z0-9_]*
constant_int 0|-[1-9][0-9]*|[1-9][0-9]*
constant_flt {constant_int}.[0-9]+
constant_chr \'[a-zA-Z0-9]\'
constant_str \"[a-zA-Z0-9]+\"
constant_bol "true"|"false"

%option noyywrap

%%
"master()" { yylval.token_name = strdup(yytext); 
    return MASTER; }

"class" { yylval.token_name = strdup(yytext); 
    return R_CLS; }

"int"|"float"|"char"|"string"|"bool" { yylval.token_name = strdup(yytext); 
    return R_TYP; }

"if"|"for"|"while" { yylval.token_name = strdup(yytext); 
    return R_SEQ; }

{something_name} { yylval.token_name = strdup(yytext); 
    return S_NME; }

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

"<-"|"=" { yylval.token_name = strdup(yytext);
    return OPERATOR_ASSIGN; }
"<"|">"|"<="|">="|"!="|"=="|"===" { yylval.token_name = strdup(yytext);
    return OPERATOR_RELTIN; }

[ \t] ;
\n {yylineno++;}
. {return yytext[0];}
