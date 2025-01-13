#include <iostream>
#include <string>

int main()
{
    char *lmao = new char[2];
    lmao[0] = 'd';
    lmao[1] = 'a';

    {
        std::string str(lmao);
        std::cout << str << '\n';
    }

    std::cout << lmao;

    delete lmao;
}