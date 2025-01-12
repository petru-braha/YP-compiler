#include <string>
#include <vector>
#include "ast_base.hpp"
#include "ast_ctrl.hpp"

/*
%{
#include <stdio.h>
#include <cstring>
#include <cmath>
#include <string>
#include <vector>
#include "util.hpp"

extern int yylex();
void yyerror(const char * s);

extern FILE* yyin;
extern char* yytext;
extern int yylineno;
extern bool method_master_started;
size_t count_error;
std::vector<symbol_table> symbols;
#define LAST_SCOPE symbols.size() - 1
%}


%left '&' '|'
%left "==" "!=" "<=" "<" ">=" ">"
%left '+' '-'
%left '*' '/' '%'
%left '(' ')'

%right '='
%right '^'


%union {
    char* information;
    unsigned char character;

    bool bool_number;
    long long intg_number;
    double real_number;
}

%token<information> MASTER TYPEOF PRINTF
%token RSV_CLSS ACS_PRIV ACS_PUBL ACS_FILD

%token<information> SMT_NAME RSV_TYPE
// %token<information> NME_INTG NME_FLOT NME_CHAR NME_STRG NME_BOOL
%token<intg_number> LIT_INTG LIT_CHAR LIT_BOOL
%token<real_number> LIT_FLOT
%token<information> LIT_STRG

%token<character> OPR_ASSIGN OPR0 OPR1 OPR2 OPR3 OPR4
%token<information> OPR_RELTON

%type<intg_number> expression_intg
%type<intg_number> term_intg
%type<intg_number> fact_intg
%type<intg_number> powr_intg

%type<real_number> expression_flot
%type<real_number> term_flot
%type<real_number> fact_flot
%type<real_number> powr_flot

%type<intg_number> expression_char
%type<intg_number> term_char
%type<intg_number> fact_char
%type<intg_number> powr_char

%type<information> expression_strg
%type<information> term_strg

%type<bool_number> expression_bool
%type<bool_number> term_bool

%start starting_symbol

%%

starting_symbol : expression;

expression: expression_intg { printf("result: %d\n", $1); }
          | expression_flot { printf("result: %f\n", $1); }
          //| expression_char { printf("result: %d\n", $1); }
          //| expression_strg { printf("result: %s\n", $1); }
          //| expression_bool { printf("result: %d\n", $1); }
          ;

expression_intg : expression_intg OPR0 term_intg {
                    if('+' == $2)
                      $$ = $1 + $3;
                    else
                      $$ = $1 - $3;
                  }
                | expression_intg OPR0 '-' term_intg {
                    if('+' == $2)
                      $$ = $1 + -1*$4;
                      else
                    $$ = $1 - -1*$4;
                  }

                | term_intg { $$ = $1; }
                ;
term_intg : fact_intg OPR1 term_intg {
              if('*' == $2)
                $$ = $1 * $3;
              else
                $$ = $1 / $3;
            }
          | fact_intg OPR3 term_intg { $$ = $1 % $3; }
          | fact_intg { $$ = $1; }
          ;
fact_intg : powr_intg OPR2 fact_intg { $$ = std::pow($1, $3); }
          | powr_intg { $$ = $1; }
          ;
powr_intg : '(' expression_intg ')' { $$ = $2; }
          | LIT_INTG { $$ = $1; }
          | SMT_NAME { $$ = 0; }
          ;

expression_flot : expression_flot OPR0 term_flot {
                    if('+' == $2)
                      $$ = $1 + $3;
                    else
                      $$ = $1 - $3;
                  }
                | expression_flot OPR0 '-' term_flot {
                    if('+' == $2)
                      $$ = $1 + -1*$4;
                    else
                      $$ = $1 - -1*$4;
                  }
                | term_flot { $$ = $1; }
                ;
term_flot : fact_flot OPR1 term_flot {
              if('*' == $2)
                $$ = $1 * $3;
              else
                $$ = $1 / $3;
            }
          | fact_flot { $$ = $1; }
          ;
fact_flot : powr_flot OPR2 fact_flot { $$ = std::pow($1, $3); }
          | powr_flot { $$ = $1; }
          ;
powr_flot : '(' expression_flot ')' { $$ = $2; }
          | LIT_FLOT { $$ = $1; }
          | SMT_NAME { $$ = 0.0; }
          ;

expression_char : term_char OPR0 expression_char {
                    if('+' == $2)
                      $$ = $1 + $3;
                    else
                      $$ = $1 - $3;
                  }
                | term_char OPR0 '-' expression_char {
                    if('+' == $2)
                      $$ = $1 + -1*$4;
                    else
                      $$ = $1 - -1*$4;
                  }
                | term_char { $$ = $1; }
                ;
term_char : term_char OPR1 fact_char {
              if('*' == $2)
                $$ = $1 * $3;
              else
                $$ = $1 / $3;
            }
          | term_char OPR3 fact_char { $$ = $1 % $3; }
          | fact_char { $$ = $1; }
          ;
fact_char : fact_char OPR2 powr_char { $$ = std::pow($1, $3); }
          | powr_char { $$ = $1; }
          ;
powr_char : '(' expression_char ')' { $$ = $2; }
          | LIT_CHAR { $$ = $1; }
          ;
expression_strg : term_strg OPR0 expression_strg {
                    if('+' == $2)
                    {
                      std::string text($1);
                      text += $3;
                      $$ = strdup(text.c_str());
                    }
                    else
                    {
                      size_t position = 0;
                      std::string text($1), token($3);
                      while(std::string::npos !=
                        (position = text.find(token, position)))
                        text.erase(position, token.length());
                      $$ = strdup(text.c_str());
                    }

                    free($1);
                    free($3);
                  }
                | term_strg { $$ = strdup($1); free($1); }
                ;
term_strg : '(' expression_strg ')' { $$ = strdup($2); free($2); }
          | LIT_STRG { $$ = strdup($1); free($1); }
          ;

expression_bool : term_bool OPR4 expression_bool {
                    if('&' == $2)
                      $$ = $1 && $3;
                    else
                      $$ = $1 || $3;
                  }
                | term_bool OPR4 '!' expression_bool {
                   if('&' == $2)
                      $$ = $1 && $4;
                    else
                      $$ = $1 || $4;
                  }
                | term_bool { $$ = $1; }
                ;
term_bool : '(' expression_bool ')' { $$ = $2; }
          | LIT_BOOL { $$ = $1; }
          | expression_intg OPR_RELTON expression_intg {
              if(0 == strcmp($2, "=="))
                $$ = $1 == $3;
              else if(0 == strcmp($2, "!="))
                $$ = $1 != $3;
              else if(0 == strcmp($2, "<="))
                $$ = $1 <= $3;
              else if(0 == strcmp($2, "<"))
                $$ = $1 < $3;
              else if(0 == strcmp($2, ">="))
                $$ = $1 >= $3;
              else if(0 == strcmp($2, ">"))
                $$ = $1 > $3;
            }
          | expression_flot OPR_RELTON expression_flot {
              if(0 == strcmp($2, "=="))
                $$ = $1 == $3;
              else if(0 == strcmp($2, "!="))
                $$ = $1 != $3;
              else if(0 == strcmp($2, "<="))
                $$ = $1 <= $3;
              else if(0 == strcmp($2, "<"))
                $$ = $1 < $3;
              else if(0 == strcmp($2, ">="))
                $$ = $1 >= $3;
              else if(0 == strcmp($2, ">"))
                $$ = $1 > $3;
            }
          | expression_char OPR_RELTON expression_char {
              if(0 == strcmp($2, "=="))
                $$ = $1 == $3;
              else if(0 == strcmp($2, "!="))
                $$ = $1 != $3;
              else if(0 == strcmp($2, "<="))
                $$ = $1 <= $3;
              else if(0 == strcmp($2, "<"))
                $$ = $1 < $3;
              else if(0 == strcmp($2, ">="))
                $$ = $1 >= $3;
              else if(0 == strcmp($2, ">"))
                $$ = $1 > $3;
            }
          | expression_strg OPR_RELTON expression_strg {
              if(0 == strcmp($2, "=="))
                $$ = $1 == $3;
              else if(0 == strcmp($2, "!="))
                $$ = $1 != $3;
              else if(0 == strcmp($2, "<="))
                $$ = $1 <= $3;
              else if(0 == strcmp($2, "<"))
                $$ = $1 < $3;
              else if(0 == strcmp($2, ">="))
                $$ = $1 >= $3;
              else if(0 == strcmp($2, ">"))
                $$ = $1 > $3;
            }
          ;

%%

void yyerror(const char * s){
  count_error++;
  printf("error - line %d: %s.\n", yylineno, s);
}

int main(int argc, char** argv)
{
  if(argc != 2)
  {
    yyerror("wrong number of arguments");
    return EXIT_FAILURE;
  }

  FILE* ptr = fopen(argv[1], "r");
  if(nullptr == ptr)
  {
    yyerror("invalid file");
    return EXIT_FAILURE;
  }

  yyin = ptr;
  yyparse();
  return EXIT_SUCCESS;
}
*/