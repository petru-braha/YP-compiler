/* YP_lexer.l - text recognition component
 * (c) authors - Braha Petru Bogdan - <petrubraha@gmail.com>
 *             - Meraru Ioan Lucian - <https://github.com/Zamdacmalfal>
 */

%{
#include <stdlib.h>
#include <stdio.h>
#include "YP_parser.tab.hpp"

void yyerror(const char * s);
bool master_started = false;

%}

/* lexical description - regex */
reserved_type "int"|"float"|"char"|"string"|"bool"
/* type_array (\[([1-9][0-9]*)\])* */

something_name [a-zA-Z_][a-zA-Z0-9_]*
literal_int 0|-[1-9][0-9]*|[1-9][0-9]*
literal_flt {literal_int}.[0-9]+
literal_chr \'[^\']\'
literal_str \"[^\"]+\"
literal_bol "true"|"false"

comment #.*

%option noyywrap

%%
"master()" { if(master_started)
    yyerror("the master method can only be declared and defined once");
    master_started = true; }


"private:" { return A_PRV; }
"public:" { return A_PUB; }
"class" { return R_CLS; }

{reserved_type} { yylval.token_name = strdup(yytext);
    return RSV_TYPE; }

"<-"|"=" { return OPR_ASSIGN; }
'+'|'-' { yylval.token_name = strdup(yytext);
    return OPR0; }
'*'|'/'|'^' { yylval.token_name = strdup(yytext);
    return OPR1; }
'%' { yylval.token_name = strdup(yytext);
    return OPR2; }
'+'|'-' { yylval.token_name = strdup(yytext);
    return OP_STRG; }
"&&"|"||" { yylval.token_name = strdup(yytext);
    return OPR3; }
"=="|"!="|"<="|"<"|">="|">" { yylval.token_name = strdup(yytext);
    return OPR_RELTN; }

{literal_int} { yylval.token_name = strdup(yytext);
    return LIT_INTG; }
{literal_flt} { yylval.token_name = strdup(yytext);
    return LIT_FLOT; }
{literal_chr} { yylval.token_name = strdup(yytext);
    return LIT_CHAR; }
{literal_str} { yylval.token_name = strdup(yytext);
    return LIT_STRG; }
{literal_bol} { yylval.token_name = strdup(yytext);
    return LIT_BOOL; }

{something_name} { yylval.token_name = strdup(yytext); 
    return SMT_NAME; }

{comment}


[ \t\r] ;
\n {yylineno++;}
. {return yytext[0];}
