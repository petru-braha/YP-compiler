#ifndef __0ERROR0__
#define __0ERROR0__

/* comments
 * a concatenation of three segments: err problem description
 */

void yyerror(const char *s);

#define ERR_SCOPE_CLSDECL yyerror("classes can only be declared globally")

#define ERR_TREAT_TYPID yyerror("type treated as identifier")
#define ERR_DEF_CLS yyerror("class already defined")
#define ERR_DEF_IDCLS yyerror("identifier already defined in class")
#define ERR_DEF_ID yyerror("identifier already defined")

#define ERR_UNDEF_TYPE yyerror("undefined type")
#define ERR_UNDEF_ARG yyerror("undefined argument")
#define ERR_UNDEF_ID yyerror("undefined identifier")

#define ERR_TYP_ITEM yyerror("wrong item type")
#define ERR_TYP_ITEMFCT yyerror("a function pointer can not be passed here")
#define ERR_TYP_NOTPRIMITIVE yyerror("the argument should be primitive")
#define ERR_TYP_PRIMITIVE yyerror("the argument should not be primitive")
#define ERR_TYP_INCOMPATIBLE yyerror("incompatible types")

#define ERR_DEF_PARAMETER yyerror("parameter already defined")
#define ERR_DEF_ATTRIBUTE yyerror("attribute already defined")
#define ERR_UNDEF_PARAMETER yyerror("parameter not found")
#define ERR_UNDEF_ATTRIBUTE yyerror("attribute not found")

#define ERR_PTR yyerror("invalid parameter pointer")

#endif
