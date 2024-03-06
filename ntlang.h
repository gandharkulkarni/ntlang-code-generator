\
/* ntlang.h - header file for project01 (ntlang) */
#include <stdbool.h> 
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

/*
 * scan.c
 */
 
/*

# Scanner EBNF

whitespace  ::=  (' ' | '\t') (' ' | '\t')*

tokenlist  ::= (token)*
token      ::= intlit | hexlit | binlit | symbol
symbol     ::= '+' | '-' | '*' | '/' | '>>' | '>-' | '<<' | '~' | '&' | '|' | '^'
intlit     ::= digit (digit)*
regname    ::= 'a0' | 'a1' | ... | 'a7'
hexlit     ::= '0x' | hexdigit (hexdigit)*
binlit     ::= '0b' ['0', '1'] (['0', '1'])*
hexdigit   ::= 'a' | ... | 'f' | 'A' | ... | 'F' | digit
digit      ::= '0' | ... | '9'

# Ignore
whitespace ::= ' ' | '\t' (' ' | '\t')*

*/


#define SCAN_TOKEN_LEN 32
#define SCAN_TABLE_LEN 1024
#define SCAN_INPUT_LEN 4096

enum scan_token_enum {
    TK_INTLIT, /* 1, 22, 403 */
    TK_PLUS,   /* + */
    TK_MINUS,  /* - */
    TK_EOT,    /* end of text */
    TK_ANY,    /* A wildcard token used for parsing */
    TK_BINLIT, /* 0b1010, 0b11110000 */
    TK_HEXLIT, /* 0x0000000A, 0x0000000B  */
    TK_HEXDIGITLIT, /* a, b, c... f */
    TK_MULT,   /* * */
    TK_DIV,    /* / */
    TK_LSR,    /* >> */
    TK_ASR,    /* >- */
    TK_LSL,    /* << */
    TK_NOT,    /* ~ */
    TK_AND,    /* & */
    TK_OR,     /* | */
    TK_XOR,    /* ^ */
    TK_LPAREN, /* ( */
    TK_RPAREN, /* ) */
    TK_REGNAME, /* a1, a2, ..... a7 */
    TK_NONE
};

#define SCAN_TOKEN_STRINGS {\
    "TK_INTLIT",\
    "TK_PLUS",\
    "TK_MINUS",\
    "TK_EOT",\
    "TK_ANY",\
    "TK_BINLIT",\
    "TK_HEXLIT",\
    "TK_HEXDIGITLIT",\
    "TK_MULT",\
    "TK_DIV",\
    "TK_LSR",\
    "TK_ASR",\
    "TK_LSL",\
    "TK_NOT",\
    "TK_AND",\
    "TK_OR",\
    "TK_XOR",\
    "TK_LPAREN",\
    "TK_RPAREN",\
    "TK_REGNAME"\
};

struct scan_token_st {
    enum scan_token_enum id;
    char value[SCAN_TOKEN_LEN];
};

struct scan_table_st {
    struct scan_token_st table[SCAN_TABLE_LEN];
    int len;
    int cur;
};

void scan_token_print(struct scan_token_st *tk);
void scan_table_init(struct scan_table_st *st);
void scan_table_scan(struct scan_table_st *st, char *input);
void scan_table_print(struct scan_table_st *st);
struct scan_token_st * scan_table_get(struct scan_table_st *st, int i);
bool scan_table_accept(struct scan_table_st *st, enum scan_token_enum tk_expected);

/*
 * parse.c
 */

/*

# Parser

program    ::= expression EOT

expression ::= operand (operator operand)*

operand    ::= intlit
             | hexlit
             | binlit
             | regname
             | '-' operand
             | '~' operand
             | '(' expression ')'
*/

enum parse_expr_enum {EX_INTVAL, EX_OPER1, EX_OPER2, EX_REG};
enum parse_oper_enum {OP_PLUS, OP_MINUS, OP_MULT, OP_DIV, OP_LSR, OP_ASR, OP_LSL, OP_NOT, OP_AND, OP_OR, OP_XOR, OP_NONE};

struct parse_oper_pair_st {
    enum scan_token_enum tkid;
    enum parse_oper_enum opid;
};


struct parse_node_st {
    enum parse_expr_enum type;
    union {
        struct {uint32_t value;} intval;
        struct {char*  name;} reg;
        struct {enum parse_oper_enum oper;
                struct parse_node_st *operand;} oper1;
        struct {enum parse_oper_enum oper;
                struct parse_node_st *left;
                struct parse_node_st *right;} oper2;
    };
};


#define PARSE_TABLE_LEN 1024

/* The parse_table_st is similar to the scan_table_st and is
 * used to allocatio parse_node_st structs so we can avoid
 * heap allocation.
 */
struct parse_table_st {
    struct parse_node_st table[PARSE_TABLE_LEN];
    int len;
};


/*
 * config
 */

struct config_st {
    char input[SCAN_INPUT_LEN];
    int base;
    int width;
    bool unsigned_flag;
    int args[8];
    bool compile_mode;
    char name[SCAN_INPUT_LEN];
};

void parse_table_init(struct parse_table_st *pt);
struct parse_node_st * parse_node_new(struct parse_table_st *pt);
struct parse_node_st * parse_program(struct parse_table_st *pt,
                                        struct scan_table_st *st);
void parse_tree_print(struct parse_node_st *np);


/*
 * eval.c
 */

uint32_t eval(struct parse_node_st *pt, struct config_st *config);
void eval_print(struct config_st *cp, uint32_t value);
uint32_t eval_get_register_value(char* reg_name);

/*
 * ntlang.c
 */ 
void parse_args(struct config_st *cp, int argc, char **argv);
void print_usage();
void ntlang_error();

/*
conv.c
*/
void convert_error(char* err);
uint32_t convert_string_to_uint32(char *str, int base);    
uint32_t convert_char_to_uint32_digit(char ch); 
char convert_uint32_digit_to_char(uint32_t digit);


/*
 * compile.c
 */
void compile_output_main(char* name);
void compile (struct parse_node_st *pt);
void compile_init(char* name);
void compile_exit();
