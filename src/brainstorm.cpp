#include <string>
#include <vector>
#include <map>

/* comments:
 * type_table <- object_data <- symbol_table <- type_table <- object_data
 */

constexpr unsigned char ITEM_TYPE_VAR = 0;
constexpr unsigned char ITEM_TYPE_FCT = 1;
constexpr unsigned char ITEM_TYPE_OBJ = 2;

class item_data
{
    const unsigned char item_type;

public:
    const unsigned char get_item_type() const;
};

//------------------------------------------------

class variable_data final : public item_data
{
    std::string type;
    std::string value;

public:
    ~variable_data() = default;
    variable_data(const std::string&);
    variable_data(const std::string&, const std::string&);

    variable_data& set_value(const std::string&);

    const std::string& get_type() const;
    const std::string& get_value() const;
};

class function_data final
{
    std::string return_type;
    std::vector<item_data*> parameters;

    // size_t lineno_begin, lineno_end;
    // std::vector<size_t> lineno_return;

public:
    ~function_data() = default;
    function_data(std::string &);
    function_data(std::string &,
                  const std::vector<item_data*> &);

    function_data& set_parameter(const size_t, const std::string&);
    
    const std::string& get_return_type() const;
    const std::string& get_parameter_type(const size_t) const;
    const std::string& get_parameter_value(const size_t) const;
};

class object_data final : public item_data
{
    std::string type;
    std::vector<item_data*> attributes;

public:
    ~object_data();
    object_data(std::string &);
    object_data(std::string &,
                const std::vector<item_data*> &);

    object_data& set_attribute(const size_t, item_data*);

    const std::string& get_type() const;
    item_data* get_attribute(const size_t) const;
};

//------------------------------------------------

class symbol_table
{
    // identifier => data
    std::map<std::string, variable_data> var;
    std::map<std::string, function_data> fct;
    std::map<std::string, object_data> obj;

public:
    ~symbol_table() = default;
    symbol_table() = default;

    symbol_table& variable_add(const std::string&, const variable_data&);
    symbol_table& function_add(const std::string&, const function_data&);
    symbol_table& object_add(const std::string&, const object_data&);

    variable_data* variable_exists(const std::string&) const;
    function_data* function_exists(const std::string&) const;
    object_data* object_exists(const std::string&) const;
};


//------------------------------------------------

std::map<std::string, symbol_table> type_table;

unsigned char type_insert(const std::string&, const symbol_table&);
const symbol_table* type_exists(const std::string&);

//------------------------------------------------

const unsigned char item_data::get_item_type() const
{
    return item_type;
}

//------------------------------------------------

variable_data::variable_data(const std::string& type)
{
    // type checking
    // set default value for the value
}

variable_data::variable_data(const std::string& type,
                            const std::string& value)
{
    // type checking
    // type compatibility
    // set value
}

variable_data& variable_data::set_value(const std::string& value)
{
    // type compatibility
    // set value
    return *this;
}

const std::string& variable_data::get_type() const
{
    std::string i_love_my_girlfriend;
    return i_love_my_girlfriend;
}

const std::string& variable_data::get_value() const;