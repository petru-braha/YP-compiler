#ifndef __0ASTAST0__
#define __0ASTAST0__

constexpr char CST_STAT_TYPE = 100;
constexpr char OPR_STAT_TYPE = 101;
constexpr char ASG_STAT_TYPE = 102;

constexpr char SYC_STAT_TYPE = 103;
constexpr char MTD_STAT_TYPE = 104;
constexpr char MTS_STAT_TYPE = 105;

constexpr char IDX_STAT_TYPE = 106;
constexpr char FLD_STAT_TYPE = 107;
constexpr char FLC_STAT_TYPE = 108;

constexpr char PMD_STAT_TYPE = 109;
constexpr char FCD_STAT_TYPE = 110;
constexpr char OBD_STAT_TYPE = 111;

constexpr char CLD_STAT_TYPE = 112;
constexpr char SCD_STAT_TYPE = 113;
constexpr char DCL_STAT_TYPE = 114;

constexpr char ACT_STAT_TYPE = 115;
constexpr char RET_STAT_TYPE = 116;

constexpr char SCP_STAT_TYPE = 117;
constexpr char SCC_STAT_TYPE = 118;

constexpr char IFE_STAT_TYPE = 119;
constexpr char WHL_STAT_TYPE = 120;
constexpr char FOR_STAT_TYPE = 121;

class ast_expression;
const char *get_buffer(ast_expression *const);

class ast_statement
{
public:
  virtual ~ast_statement() = default;

  virtual void *evaluate() = 0;

  virtual const char get_stat_type() const = 0;
};

class ast_expression : public ast_statement
{
public:
  virtual ~ast_expression() = default;
};

#endif
