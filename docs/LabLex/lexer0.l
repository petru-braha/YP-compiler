%{
#include <iostream>
%}

idnt [a-zA-Z_][a-zA-Z_]*
type "int"|"float"
intg [1-9][0-9]*

%x comment

%option noyywrap

%%
{type} {std::cout << "recognized type: " << yytext << '\n';}
{idnt} {std::cout << "recognized id: " << yytext << '\n';}
{intg} {std::cout << "recognized number: " << yytext << '\n';}

"/*" {std::cout << "recognized comment start"; BEGIN comment;}
<comment>"*/" {std::cout << "recognized comment end"; BEGIN 0;}
<comment>.|\n {ECHO;}
%%

int main(int argc, char** argv)
{
    FILE *g;
    if(argc > 0)
        yyin = fopen(argv[1],"r");

/*if(!(g = fopen("out.txt","w")))
    fstd::cout(stderr,"eroare creare fisier!");
else
 yyout=g; */

    yylex();
    return 0;
}
