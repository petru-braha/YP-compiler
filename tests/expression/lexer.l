%{
  #include <stdlib.h>
  #include <stdio.h>
  #include "parse.tab.hpp"

  void yyerror(const char * s);

  constexpr char EE_CHR = 'a';
  constexpr char NE_CHR = 'b';
  constexpr char LE_CHR = 'c';
  constexpr char LS_CHR = 'd';
  constexpr char GE_CHR = 'e';
  constexpr char GS_CHR = 'f';
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

"==" { yylval.character = EE_CHR; return OPR_RELTON; }
"!=" { yylval.character = NE_CHR; return OPR_RELTON; }
"<=" { yylval.character = LE_CHR; return OPR_RELTON; }
"<"  { yylval.character = LS_CHR; return OPR_RELTON; }
">=" { yylval.character = GE_CHR; return OPR_RELTON; }
">"  { yylval.character = GS_CHR; return OPR_RELTON; }

{literal_int} { yylval.information = strdup(yytext);
  return LIT_INTG; }
{literal_flt} { yylval.information = strdup(yytext);
  return LIT_FLOT; }
{literal_chr} { yylval.information = strdup(yytext);
  return LIT_CHAR; }
{literal_str} { yylval.information = strdup(yytext);
  return LIT_STRG; }
{literal_bol} { yylval.information = strdup(yytext);
  return LIT_BOOL; }

{comment}


[ \t\r] ;
\n { yylineno++; }
. { return yytext[0]; }
