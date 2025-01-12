/* YP_lexer.l - text recognition component
 * (c) authors - Braha Petru Bogdan - <petrubraha@gmail.com>
 *             - Meraru Ioan Lucian - <https://github.com/Zamdacmalfal>
 */

%{
#include <stdlib.h>
#include <stdio.h>
#include "parse.tab.hpp"

void yyerror(const char * s);
bool master_started = false;

%}

/* lexical description - regex */
/* reserved_type "int"|"float"|"char"|"string"|"bool" */
/* type_array (\[([1-9][0-9]*)\])* */

something_name [a-zA-Z_][a-zA-Z0-9_]*
literal_int 0|-[1-9][0-9]*|[1-9][0-9]*
literal_flt {literal_int}.[0-9]+
literal_chr \'[^\']\'
literal_str \"[^\"]+\"
literal_bol "true"|"false"

comment #.*

/*
"int "{something_name}    { yylval.information = strdup(yytext + 4); return NME_INTG; }
"float "{something_name}  { yylval.information = strdup(yytext + 6); return NME_FLOT; }
"char "{something_name}   { yylval.information = strdup(yytext + 5); return NME_CHAR; }
"string "{something_name} { yylval.information = strdup(yytext + 7); return NME_STRG; }
"bool "{something_name}   { yylval.information = strdup(yytext + 5); return NME_BOOL; }
*/

%option noyywrap

%%
"Print" { return PRINTF; }
"Type"  { return TYPEOF; }
"master()" { if(master_started)
  yyerror("the master method can only be declared and defined once");
  master_started = true; }

"class" { return RSV_CLSS; }
"private:" { return ACS_PRIV; }
"public:" { return ACS_PUBL; }

"<-"|"="  { return OPR_ASSIGN; }
"+"|"-"   { yylval.character = *yytext; return OPR0; }
"*"|"/"   { yylval.character = *yytext; return OPR1; }
"^"       { yylval.character = *yytext; return OPR2; }
"%"       { yylval.character = *yytext; return OPR3; }
"&"|"|"   { yylval.character = *yytext; return OPR4; }
"=="|"!="|"<="|"<"|">="|">" { yylval.information = strdup(yytext);
  return OPR_RELTON; }

{literal_int} { yylval.intg_number = atoll(yytext);
  return LIT_INTG; }
{literal_flt} { yylval.real_number = atof(yytext);
  return LIT_FLOT; }
{literal_chr} { yylval.intg_number = yytext[1];
  return LIT_CHAR; }
{literal_str} { yytext[strlen(yytext) - 1] = '\0';
  yylval.information = strdup(yytext + 1);
  return LIT_STRG; }
{literal_bol} { yylval.bool_number = (bool)strcmp(yytext, "false");
  return LIT_BOOL; }

{something_name} { yylval.information = strdup(yytext);
  return SMT_NAME; }

{comment}


[ \t\r] ;
\n { yylineno++; }
. { return yytext[0]; }
