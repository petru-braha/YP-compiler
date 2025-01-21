#include <iostream>

class a
{
    public:
    virtual void print() const = 0;
};

class b : public a
{
    public:
    void print() const override
    {
        std::cout << "b";
    }
};
class c : public a
{
    public:
    void print() const override
    {
        std::cout << "c";
    }
};

int main()
{
    a * obj = new b;
    obj->print();
}
