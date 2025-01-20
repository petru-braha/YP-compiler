#include <iostream>
#include <unordered_map>

std::unordered_map<char, int *> *word = new std::unordered_map<char, int *>;

int f1()
{
    {
        int variable = 5;
        std::pair<char, int *> v_pair('a', &variable);
        word->insert(v_pair);
    }

    // it is expected to print 5
    if (5 != *(word->at('a')))
        return 1;

    // it is expected to print 5
    std::unordered_map<char, int *> text(*word);
    delete word;
    if (5 != *(text.at('a')))
        return 1;
    return 0;
}

int f2()
{
    int *variable = new int(5);
    std::pair<char, int *> v_pair('a', variable);
    word->insert(v_pair);

    // it is expected to print 5
    delete variable;
    if (5 != *(word->at('a')))
        return 1;

    // it is expected to print 5
    std::unordered_map<char, int *> text(*word);
    delete word;
    if (5 != *(text.at('a')))
        return 1;
    return 0;
}

int main()
{
    // f1() vs f2()
    if (f2())
        std::cout << "fail\n";
}
