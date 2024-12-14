#include <string>

class type_data
{
    std::string *data;
    public:
    type_data(std::string *type, int n);
    ~type_data();

};
type_data::type_data(std::string *type, int n)
{
    data = new std::string[n];
    for(int i = 0; i<n; i++)
    {
        data[i] = type[i];
    }
}

type_data::~type_data()
{
    delete[]data;
}

