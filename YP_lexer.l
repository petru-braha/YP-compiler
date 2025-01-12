/* YP_lexer.l - text recognition component
 * (c) authors - Braha Petru Bogdan - <petrubraha@gmail.com>
 *             - Meraru Ioan Lucian - <https://github.com/Zamdacmalfal>
 */

%{
#include <stdlib.h>
#include <stdio.h>
#include "parse.tab.hpp"

void yyerror(const char * s);
%}

/* lexical description - regex */
reserved_type "int"|"float"|"char"|"string"|"bool"
reserved_type_array {reserved_type}(\[([1-9][0-9]*)\])*
enclosed_type_array {something_name}(\[([1-9][0-9]*)\])*

something_name [a-zA-Z_][a-zA-Z0-9_]*
literal_int 0|-[1-9][0-9]*|[1-9][0-9]*
literal_flt {literal_int}.[0-9]+
literal_chr \'[^\']\'
literal_str \"[^\"]+\"
literal_bol "true"|"false"

comment #.*

%option noyywrap

%%

"print"     { return PRINTF; }
"type"      { return TYPEOF; }
"master()"  { return MASTER; }
"{" { return SCOPE_BEGIN; }
"}" { return SCOPE_END; }

"class"    { return RSV_CLSS; }
"private:" { return ACS_PRIV; }
"public:"  { return ACS_PUBL; }

"<-"|"="        { return OPR_ASSIGN; }
"!"|"-"         { yylval.character = *yytext; return OPRU; }
"+"|"-"|"&"|"|" { yylval.character = *yytext; return OPR0; }
"*"|"/"|"%"     { yylval.character = *yytext; return OPR1; }
"^"             { yylval.character = *yytext; return OPR2; }
"=="|"!="|"<="|"<"|">="|">" { yylval.information = strdup(yytext);
  return OPR_RELTON; }

"break"    { return ACT_BREK; }
"continue" { return ACT_CONT; }
"return"   { return ACT_RTRN; }

"if"    { return SEQ_IFIF; }
"else"  { return SEQ_ELSE; }
"while" { return SEQ_WHLE; }
"for"   { return SEQ_FOOR; }

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

{reserved_type}       { yylval.information = strdup(yytext); return RSV_TYPE; }
{reserved_type_array} { yylval.information = strdup(yytext); return RSV_ARRY; }
{something_name}      { yylval.information = strdup(yytext); return SMT_NAME; }
{enclosed_type_array} { yylval.information = strdup(yytext); return DEF_ARRY; }

{comment}


[ \t\r] ;
\n { yylineno++; }
. { return yytext[0]; }
