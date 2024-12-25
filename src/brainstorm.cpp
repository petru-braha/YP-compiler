#include <string>
#include <vector>
#include <map>

class symbol_table;
std::map<std::string, symbol_table> type_table;

class variable_data
{
    std::string type;
    std::string value;

public:
    ~variable_data() = default;
    variable_data(const std::string &);
    variable_data(const std::string &, const std::string &);

    void set_value();

    void get_type() const;
    void get_value() const;
};

class function_data
{
    std::string return_type;
    std::vector<variable_data> parameters;

    // size_t lineno_begin, lineno_end;
    // std::vector<size_t> lineno_return;

public:
    ~function_data() = default;
    function_data(std::string &);
    function_data(std::string &,
                  const std::vector<variable_data> &);

    void get_type() const;
    void get_type() const;
};

class object_data
{
    std::string type;
    std::vector<variable_data> attributes;
    // std::vector<function_data> methods;

public:
    ~object_data();
    object_data(std::string &);
    object_data(std::string &,
                const std::vector<variable_data> &);

    void get_type() const;
    void get_attribute() const;
};

class symbol_table
{
    // identifier => data
    std::map<std::string, variable_data> var;
    std::map<std::string, function_data> fct;
    std::map<std::string, object_data> obj;

public:
    ~symbol_table() = default;
    symbol_table() = default;

    void variable_add();
    void function_add();
    void object_add();

    const variable_data* variable_exists(const char *) const;
    const function_data* function_exists(const char *) const;
    const object_data* object_exists(const char *) const;
};

std::map<std::string, symbol_table> type_table;

void type_insert();
void type_exists();

// <- object_data <- symbol_table <- type_table <- object