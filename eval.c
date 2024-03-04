/* eval.c - tree evaluation and value printing */

#include "ntlang.h"

void eval_error(char *err) {
    printf("eval_error: %s\n", err);
    exit(-1);
}

uint32_t eval(struct parse_node_st *pt) {
    uint32_t v1, v2;

    if (pt->type == EX_INTVAL) {
        v1 = pt->intval.value;
    } else if (pt->type == EX_OPER1) {
        v1 = eval(pt->oper1.operand);
        if (pt->oper1.oper == OP_MINUS) {
            v1 = -v1;
        } else if (pt->oper1.oper == OP_NOT) {
            v1 = ~v1;
        } else {
       		eval_error("Bad operator");
        }
    } else if (pt->type == EX_OPER2) {
        v1 = eval(pt->oper2.left);
        v2 = eval(pt->oper2.right);
        if (pt->oper2.oper == OP_PLUS) {
            v1 = v1 + v2;
        } else if (pt->oper2.oper == OP_MINUS) {
            v1 = v1 - v2;
        } else if (pt->oper2.oper == OP_MULT) {
            v1 = v1 * v2;
        } else if (pt->oper2.oper == OP_DIV) {
        	if(v2 != 0) {
        		v1 = v1 / v2;	
        	} else{
        		eval_error("Division by zero"); 
        	}
        } else if (pt->oper2.oper == OP_LSR) {
            v1 = v1 >> v2;
        } else if (pt->oper2.oper == OP_ASR) {
            v1 = (uint32_t)(((int32_t) v1) >> v2);
        } else if (pt->oper2.oper == OP_LSL) {
            v1 = v1 << v2;
        } else if (pt->oper2.oper == OP_AND) {
            v1 = v1 & v2;
        } else if (pt->oper2.oper == OP_OR) {
            v1 = v1 | v2;
        } else if (pt->oper2.oper == OP_XOR) {
            v1 = v1 ^ v2;
        } else {
            eval_error("Bad operator");            
        }
    }

    return v1;
}

/**
Reverse array elements
*/
void eval_reverse_array(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; ++i) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

/**
generates output string and populates output array based on width
*/
int eval_generate_output(uint32_t value, char* output, int base, int width) {
    int i = 0;
    if(base==16) {
        width = width/4;
    }
    while(i<width) {
        uint32_t temp = value % base;
        output[i++] = convert_uint32_digit_to_char(temp);
        value = value / base;
    }
    return i;
	
}
/**
Generates and applies mask to given value
*/
uint32_t eval_use_mask(uint32_t value, int width) {
    uint32_t mask = (width == 32) ?  0xFFFFFFFF : (1 << width) - 1;
    value = value & mask;
    
    return value;
}

/**
Adds prefix and prints generated output 
*/
void eval_print_output(uint32_t value, int base, int width, char prefix) {
    char output[64];

    value = eval_use_mask(value, width);

    int i = eval_generate_output(value, output, base, width);
    output[i++] = prefix;
    output[i++] = '0';
    output[i] = '\0';
    eval_reverse_array(output);
    printf("%s\n", output);
}


/**
Generates and prints output in base 10 format
*/
void eval_print_output_in_base10 (uint32_t value, int base, int width, bool unsigned_flag) {
    char output[64];
    value = eval_use_mask(value, width);
    int i = 0;

    /* Base case if value is zero, while loop will not execute. */
    if(value==0){
        output[i++] = '0';
    }

    bool is_negative = false;
    if(unsigned_flag==false) {
        is_negative = (value >> (width - 1)) & 1;
        if (is_negative) {
            value = (~value) + 1;
            /* Removing unnecessary MSB that was set due to 2's complement operation  */
            value = eval_use_mask(value,width);
        }
    }
    while(value!=0) {
        uint32_t temp = value % base;
        output[i++] = convert_uint32_digit_to_char(temp);
        value = value / base;
    }

    if (is_negative) {
        output[i++] = '-';
    }
    output[i] = '\0';
    eval_reverse_array(output);
    printf("%s\n", output);
}

/**
Prints output of evaluated expression based on config parameters 
*/
void eval_print(struct config_st *cp, uint32_t value) {
    if(cp->base==10) {
        eval_print_output_in_base10(value, cp->base, cp->width, cp->unsigned_flag);
    } else if(cp->base==2) {
        eval_print_output(value, cp->base,cp-> width, 'b');
    } else if(cp->base==16) {
        eval_print_output(value, cp->base,cp-> width, 'x');
    }
}
