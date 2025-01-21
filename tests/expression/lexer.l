%{
  #include <stdlib.h>
  #include <stdio.h>
  #include "parse.tab.hpp"
  #include "alphabet.hpp"

  void yyerror(const char * s);
%}

/* lexical description - regex */
literal_intg 0|-[1-9][0-9]*|[1-9][0-9]*
literal_flot {literal_intg}\.[0-9]+
literal_char \'[^\']\'
literal_strg \"[^\"]+\"
literal_bool "true"|"false"

comment #.*

%option noyywrap

%%
"!("|"-("       { yylval.character = *yytext; return OPRU; }
"+"|"-"|"&"|"|" { yylval.character = *yytext; return OPR0; }
"⊕"            { yylval.character = XOR_CHR; return OPR0; }
"*"|"/"|"%"     { yylval.character = *yytext; return OPR1; }
"^"             { yylval.character = *yytext; return OPR2; }

"==" { yylval.character = EE_CHR; return OPR_RELTON; }
"!=" { yylval.character = NE_CHR; return OPR_RELTON; }
"<=" { yylval.character = LE_CHR; return OPR_RELTON; }
"<"  { yylval.character = LS_CHR; return OPR_RELTON; }
">=" { yylval.character = GE_CHR; return OPR_RELTON; }
">"  { yylval.character = GS_CHR; return OPR_RELTON; }

{literal_intg}|{literal_flot}|{literal_char}|{literal_strg}|{literal_bool} {
  yylval.information = strdup(yytext);
  return LITERAL; }

{comment}

[ \t\r] ;
\n { yylineno++; }
. { return yytext[0]; }
