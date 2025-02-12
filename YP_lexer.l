/* YP_lexer.l - text recognition component
 * (c) authors - Braha Petru Bogdan - <petrubraha@gmail.com>
 *             - Meraru Ioan Lucian - <https://github.com/Zamdacmalfal>
 */

%{
  #include <stdlib.h>
  #include <stdio.h>
  #include "YP_parser.tab.hpp"
  #include "src/class/dev/ast_alphabet.hpp"

  void yyerror(const char * s);
%}

/* lexical description - regex */
reserved_type "int"|"float"|"char"|"string"|"bool"
reserved_type_array {reserved_type}(\[([1-9][0-9]*)\])*
enclosed_type_array {something_name}(\[([1-9][0-9]*)\])*

something_name [a-zA-Z_][a-zA-Z0-9_]*

literal_intg 0|-[1-9][0-9]*|[1-9][0-9]*
literal_flot {literal_intg}\.[0-9]+
literal_char \'[^\']\'
literal_strg \"[^\"]+\"
literal_bool "true"|"false"

comment #.*

%option noyywrap

%%

"{" { return SCOPE_BEGIN; }
"}" { return SCOPE_END; }

"type_of"  { return TYPEOF; }
"print_f"  { return PRINTF; }
"master()" { return MASTER; }

"class"    { return RSV_CLSS; }
"private:" { return ACS_PRIV; }
"public:"  { return ACS_PUBL; }
"."|"->"   { return ACS_FILD; }

"+"|"-"|"&"|"|" { yylval.character = *yytext; return OPR0; }
"⊕"|"XOR"      { yylval.character = XOR_CHR; return OPR0; }
"=="            { yylval.character = EE_CHR; return OPR0; }
"!="            { yylval.character = NE_CHR; return OPR0; }
"<="            { yylval.character = LE_CHR; return OPR0; }
"<"             { yylval.character = LS_CHR; return OPR0; }
">="            { yylval.character = GE_CHR; return OPR0; }
">"             { yylval.character = GS_CHR; return OPR0; }
"*"|"/"|"%"     { yylval.character = *yytext; return OPR1; }
"^"             { yylval.character = *yytext; return OPR2; }
"<-"|"="        { yylval.character = ASG_CHR; return OPR3; }
"!("|"-("       { yylval.character = *yytext; return OPRU; }

{literal_intg}|{literal_flot}|{literal_char}|{literal_strg}|{literal_bool} {
  yylval.information = strdup(yytext);
  return LITERAL; }

"break"    { return ACT_BREK; }
"continue" { return ACT_CONT; }
"return"   { return ACT_RTRN; }

"if"    { return SEQ_IFIF; }
"else"  { return SEQ_ELSE; }
"while" { return SEQ_WHLE; }
"for"   { return SEQ_FOOR; }

{reserved_type}       { yylval.information = strdup(yytext); return RSV_TYPE; }
{reserved_type_array} { yylval.information = strdup(yytext); return RSV_ARRY; }
{something_name}      { yylval.information = strdup(yytext); return SMT_NAME; }
{enclosed_type_array} { yylval.information = strdup(yytext); return DEF_ARRY; }

{comment}

[ \t\r] ;
\n { yylineno++; }
. { return yytext[0]; }
