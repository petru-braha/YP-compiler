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


"master()" { if(master_started)
    yyerror("the master method can only be declared and defined once");
    master_started = true; }


"private:" { return A_PRV; }
"public:" { return A_PUB; }
"class" { return R_CLS; }

{reserved_type}{type_array} { yylval.token_name = strdup(yytext);
    return R_TYP; }

'+'|'-'|'*'|'/'|'%'|'^' { yylval.token_name = strdup(yytext);
    return OP_INT; }
'+'|'-'|'*'|'/'|'^' { yylval.token_name = strdup(yytext);
    return OP_FLT; }
'+'|'-'|'*'|'/'|'%'|'^' { yylval.token_name = strdup(yytext);
    return OP_INT; }
'+'|'-' { yylval.token_name = strdup(yytext);
    return OP_STR; }
'=''='|'!''=' { yylval.token_name = strdup(yytext);
    return OP_BOL; }
'!' { yylval.token_name = strdup(yytext);
    return U_OP_BOL; }

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

{comment}

"<-"|"=" { return OPERATOR_ASSIGN; }


[ \t\r] ;
\n {yylineno++;}
. {return yytext[0];}
