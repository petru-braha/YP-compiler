#include <string>
#include <vector>
#include <map>

void yyerror(const char *s);

/* comments:
 * type_table <- object_data <- symbol_table <- type_table <- object_data
 */

constexpr unsigned char ITEM_TYPE_VAR = 0;
constexpr unsigned char ITEM_TYPE_FCT = 1;
constexpr unsigned char ITEM_TYPE_OBJ = 2;

class item_data
{
    unsigned char item_type;
    std::string type;

protected:
    void set_item_type(const unsigned int);

public:
    ~item_data() = default;
    item_data() = delete;
    item_data(const unsigned char,
              const std::string &);

    const unsigned char get_item_type() const;
    const std::string &get_type() const;
};

//------------------------------------------------

#include <string.h>

const char *DATA_TYPE_INT = "int";
const char *DATA_TYPE_FLT = "float";
const char *DATA_TYPE_CHR = "char";
const char *DATA_TYPE_STR = "string";
const char *DATA_TYPE_BOL = "bool";
const char *RESERVED_TYPES[] =
    {DATA_TYPE_INT, DATA_TYPE_FLT,
     DATA_TYPE_CHR, DATA_TYPE_STR,
     DATA_TYPE_BOL};
constexpr unsigned char COUNT_RESERVED_TYPES = 5;

bool is_primitive(const std::string &type)
{
    for (unsigned char i = 0; i < COUNT_RESERVED_TYPES; i++)
        if (0 == strcmp(RESERVED_TYPES[i], type.c_str()))
            return true;
    return false;
}

std::string default_value_of(const std::string &type)
{
    if (0 == strcmp(DATA_TYPE_INT, type.c_str()))
        return "0";
    if (0 == strcmp(DATA_TYPE_FLT, type.c_str()))
        return "0.0";
    if (0 == strcmp(DATA_TYPE_CHR, type.c_str()))
        return "\'\'";
    if (0 == strcmp(DATA_TYPE_STR, type.c_str()))
        return "\"\"";
    if (0 == strcmp(DATA_TYPE_BOL, type.c_str()))
        return "false";

    // not primitive
    return "";
}

std::string type_of(const std::string &primitive_value)
{
    switch (primitive_value.at(0))
    {
    default:
        if (primitive_value.find('.') != std::string::npos)
            return DATA_TYPE_INT;
        return DATA_TYPE_FLT;
    case '\'':
        return DATA_TYPE_CHR;
    case '\"':
        return DATA_TYPE_STR;
    case 't':
        return DATA_TYPE_BOL;
    case 'f':
        return DATA_TYPE_BOL;
    }
}

class variable_data final : public item_data
{
    std::string value;

public:
    ~variable_data() = default;
    variable_data(const std::string &);
    variable_data(const std::string &, const std::string &);

    variable_data &set_value(const std::string &);

    const std::string &get_value() const;
};

class function_data final
{
    std::string return_type;
    std::vector<item_data *> parameters;

public:
    ~function_data() = default;
    function_data(std::string &);
    function_data(std::string &,
                  const std::vector<item_data *> &);

    function_data &set_parameter(const size_t,
                                 const item_data *const);

    const std::string &get_return_type() const;
    const std::string &get_parameter_type(const size_t) const;
    const std::string &get_parameter_value(const size_t) const;
};

// the methods will be stored in the type table
class object_data final : public item_data
{
    std::vector<item_data *> attributes;

public:
    ~object_data() = default;
    object_data(std::string &);
    object_data(std::string &,
                const std::vector<item_data *> &);

    object_data &set_attribute(const size_t,
                               item_data *const);

    item_data *get_attribute(const size_t) const;
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

    symbol_table &variable_add(const std::string &, const variable_data &);
    symbol_table &function_add(const std::string &, const function_data &);
    symbol_table &object_add(const std::string &, const object_data &);

    variable_data *variable_exists(const std::string &) const;
    function_data *function_exists(const std::string &) const;
    object_data *object_exists(const std::string &) const;
};

//------------------------------------------------

std::map<std::string, symbol_table> type_table;

unsigned char type_insert(const std::string &, const symbol_table &);
const symbol_table *type_exists(const std::string &);

//------------------------------------------------

/* why it is allowed?
 * this parent class only connects derived classes
 * the actual checkings are individual for both variable_data and object_data
 */
void item_data::set_item_type(const unsigned int i_t)
{
    if (i_t > ITEM_TYPE_OBJ)
        yyerror("item data initialization - wrong parameter");
    item_type = i_t;
}

item_data::item_data(const unsigned char i_t,
                     const std::string &t)
    : item_type(i_t), type(t)
{
    if (i_t > ITEM_TYPE_OBJ)
        yyerror("item data initialization - wrong parameter");
}

const unsigned char item_data::get_item_type() const
{
    return item_type;
}

const std::string &item_data::get_type() const
{
    return type;
}

//------------------------------------------------
//! variable

variable_data::variable_data(const std::string &type)
    : item_data(ITEM_TYPE_VAR, type)
{
    if (false == is_primitive(type))
        yyerror("variable data initialization - not primitive type");
    value = default_value_of(type);
}

variable_data::variable_data(const std::string &type,
                             const std::string &value)
    : item_data(ITEM_TYPE_VAR, type)
{
    if (false == is_primitive(type))
        yyerror("variable data initialization - not primitive type");
    if (this->get_type() != type_of(value))
        yyerror("variable data initialization - not compatible types");
    this->value = value;
}

variable_data &variable_data::set_value(const std::string &value)
{
    if (this->get_type() != type_of(value))
        yyerror("variable data initialization - not compatible types");

    this->value = value;
    return *this;
}

const std::string &variable_data::get_value() const
{
    return value;
}

//! function

// no parameters
function_data::function_data(std::string &type)
    : return_type(type) {}

function_data::
    function_data(std::string &type,
                  const std::vector<item_data *> &param)
    : return_type(type), parameters()
{
    for (size_t i = 0; i < param.size(); i++)
    {
        item_data *data = param[i];
        if (ITEM_TYPE_VAR == data->get_item_type())
        {
            // variable_data *v_data = dynamic_cast<variable_data *>(data);
        }
    }
}

// to be called for every parameter - calling the function
function_data &function_data::
    set_parameter(const size_t index, const item_data *const value)
{
    if (index > parameters.size())
        yyerror("function data setting - wrong index");

    // variable
    if (ITEM_TYPE_VAR == parameters.at(index)->get_item_type())
    {
        // type compatibility
        // set value
        return *this;
    }

    // object
    // type compatibility
    // set value // value should be similar to this { 1, "lmao" }
    return *this;
}

const std::string &function_data::get_return_type() const
{
    return return_type;
}

const std::string &function_data::
    get_parameter_type(const size_t index) const
{
}

const std::string &function_data::
    get_parameter_value(const size_t index) const
{
}

//! object
object_data::object_data(std::string &type)
    : item_data(ITEM_TYPE_OBJ, type)
{
    // type checking - is it a primitive?
}

object_data::
    object_data(std::string &type,
                const std::vector<item_data *> &attributes)
    : item_data(ITEM_TYPE_OBJ, type)
{
}

object_data &object_data::
    set_attribute(const size_t index, item_data *const att)
{
    if (index >= attributes.size())
        yyerror("object data setting - wrong index");

    attributes[index] = att;
}

item_data *object_data::
    get_attribute(const size_t index) const
{
    if (index >= attributes.size())
        yyerror("object data setting - wrong index");
    return this->attributes.at(index);
}

//------------------------------------------------
/*
instance_data::instance_data(const char *d_t, const char *line)
    : item_type(ITEM_TYPE_VAR), data_type(d_t),
      instance_synopsis(nullptr)
{
    // verification
    if (nullptr == d_t)
        yyerror("instance_data: wrong parameters");

    // define item_type
    bool reserved = false;
    for (size_t i = 0; i < COUNT_RESERVED_TYPES; i++)
        if (data_type.find(RESERVED_TYPES[i]) != std::string::npos)
        {
            reserved = true;
            break;
        }

    if (nullptr == line) // not a f
    {
        if (false == reserved)
            item_type = ITEM_TYPE_OBJ;
    }
    else
    {
        if (std::string::npos ==
            data_type.find("(")) // not a f
            if (false == reserved)
                item_type = ITEM_TYPE_OBJ;
        item_type = ITEM_TYPE_FCT;
    }

    // define synopsis
    /*  switch (item_type)
      {
      case ITEM_TYPE_VAR: //
          this->instance_synopsis =
              new synopsis_variable(line);
          break;
      case ITEM_TYPE_FCT:
          this->instance_synopsis =
              new synopsis_function(line);
          break;
      case ITEM_TYPE_OBJ:
          this->instance_synopsis =
              new synopsis_class(line);
          break;

      default:
          std::cout << "error - instance data: wrong item type.\n";
          break;
      }
*/ 
