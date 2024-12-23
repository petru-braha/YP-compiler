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
"Print("{constant_int}")" { return method_print; }
"Print("{constant_flt}")" { return method_print; }
"Print("{constant_chr}")" { return method_print; }
"Print("{constant_str}")" { return method_print; }
"Print("{constant_bol}")" { return method_print; }
"Print("{something_name}")" { yylval.token_name = strdup(yytext); return method_print; }
"Type("{something_name}")" { return method_type; }

"master()" { if(master_started)
    yyerror("the master method can only be declared and defined once");
    master_started = true; }

"->"|"." { return A_FLD; } /* for both type.field and object.field */
"private:" { return A_PRV; }
"public:" { return A_PUB; }
"class" { return R_CLS; }

{reserved_type}{type_array} { yylval.token_name = strdup(yytext); 
    return R_TYP; }

"if" { return R_SEQ_IF; }
"for" { return R_SEQ_FOR; }
"while" { return R_SEQ_WHL; }

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
"<"|">"|"<="|">="|"!="|"=="|"===" { yylval.token_name = strdup(yytext);
    return OPERATOR_RELTIN; }

[ \t\r] ;
\n {yylineno++;}
. {return yytext[0];}
