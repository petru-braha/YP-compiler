#include <iostream>

class a
{
};
class b
{
};

class var : public a, public b
{
    int a;
};
class fct : public a
{
};
class obj : public a, public b
{
    char l;
};

void f(b *value)
{
    var *variable = nullptr;
    variable = static_cast<var *>(value);
    if (nullptr == variable)
    {
        obj *object = nullptr;
        object = static_cast<obj *>(value);
        if (nullptr == object)
            std::cout << "fail";
        else
            std::cout << "object";
    }
    else
        std::cout << "variable";
}

int main()
{
    obj dada;
    f(&dada);
    // prints variable => not reliable
}