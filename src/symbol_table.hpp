#include <iostream>
#include <map>
#include <string>

class id_data
{
    std::string type, type_id, name;
    // ParamList params;
public:
    id_data();
    id_data(const char *type, const char *name, const char *idType);
};

class symbol_table
{
    std::map<std::string, id_data> ids;
    std::string name;

public:
    ~symbol_table();
    symbol_table(const char *name);

    bool existsId(const char *s);
    void addVar(const char *type, const char *name);
    void printVars();
};
