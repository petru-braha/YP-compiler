%{
  #include <stdlib.h>
  #include <stdio.h>
  #include "parse.tab.hpp"

  void yyerror(const char * s);
%}

/* lexical description - regex */
literal_int 0|-[1-9][0-9]*|[1-9][0-9]*
literal_flt {literal_int}\.[0-9]+
literal_chr \'[^\']\'
literal_str \"[^\"]+\"
literal_bol "true"|"false"

comment #.*

%option noyywrap

%%
"!("|"-("       { yylval.character = *yytext; return OPRU; }
"+"|"-"|"&"|"|" { yylval.character = *yytext; return OPR0; }
"*"|"/"|"%"     { yylval.character = *yytext; return OPR1; }
"^"             { yylval.character = *yytext; return OPR2; }
"=="|"!="|"<="|"<"|">="|">" { yylval.information = strdup(yytext);
  return OPR_RELTON; }

{literal_int} { yylval.intg_number = atoll(yytext);
  return LIT_INTG; }
{literal_flt} { yylval.real_number = atof(yytext);
  return LIT_FLOT; }
{literal_chr} { yylval.information = strdup(yytext);
  return LIT_CHAR; }
{literal_str} { yylval.information = strdup(yytext);
  return LIT_STRG; }
{literal_bol} { yylval.bool_number = (bool)strcmp(yytext, "false");
  return LIT_BOOL; }

{comment}


[ \t\r] ;
\n { yylineno++; }
. { return yytext[0]; }
