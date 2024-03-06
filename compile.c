#include "ntlang.h"

void compile_error(char *err) {
    printf("compile_error: %s\n", err);
    exit(-1);
}

void compile_init(char* name) {
    char* main_filename = "codegen_main.s";
    compile_output_main(main_filename);
    printf(".global codegen_func_s\n");
    printf("codegen_func_s:\n");
    printf("%s:\n", name);
    printf("\taddi sp, sp, -8\n");
    printf("\tsd ra, (sp)\n");
}
void compile_exit() {
    printf("\tld a0, (sp)\n");
    printf("\taddi sp, sp, 8\n");
    printf("\tld ra, (sp)\n");
    printf("\taddi sp, sp, 8\n");
    printf("\tret\n");
}

void compile_unary_operation(struct parse_node_st *pt) {
    if (pt->oper1.oper == OP_MINUS) {
        printf("\tsub t0, zero, t0\n");    
    } else if (pt->oper1.oper == OP_NOT) {
        printf("\tli t1, -1\n");
        printf("\txor t0, t0, t1\n");
    } else {
   		compile_error("Bad operator");
    }
    printf("\taddi sp, sp, -8\n");
    printf("\tsd t0, (sp)\n");
}

void compile_binary_operation(struct parse_node_st *pt) {
    if (pt->oper2.oper == OP_PLUS) {
        printf("\tadd t0, t0, t1\n");
    } else if (pt->oper2.oper == OP_MINUS) {
        printf("\tsub t0, t0, t1\n");
    } else if (pt->oper2.oper == OP_MULT) {
        printf("\tmul t0, t0, t1\n");
    } else if (pt->oper2.oper == OP_DIV) {
		printf("\tdiv t0, t0, t1\n");    	
    } else if (pt->oper2.oper == OP_LSR) {
        printf("\tsrl t0, t0, t1\n");
    } else if (pt->oper2.oper == OP_ASR) {
        printf("\tsra t0, t0, t1\n");        
    } else if (pt->oper2.oper == OP_LSL) {
        printf("\tsll t0, t0, t1\n");        
    } else if (pt->oper2.oper == OP_AND) {
        printf("\tand t0, t0, t1\n");
    } else if (pt->oper2.oper == OP_OR) {
        printf("\tor t0, t0, t1\n");
    } else if (pt->oper2.oper == OP_XOR) {
        printf("\txor t0, t0, t1\n");
    } else {
        compile_error("Bad operator");            
    }
    printf("\taddi sp, sp, -8\n");
    printf("\tsd t0, (sp)\n");
}

void compile (struct parse_node_st *pt) {
    if (pt->type == EX_INTVAL){
        printf("\taddi sp, sp, -8\n");
        printf("\tli t0, %d\n", pt->intval.value);
        printf("\tsd t0, (sp)\n");
    }
    else if (pt->type == EX_REG) {
        printf("\taddi sp, sp, -8\n");
        printf("\tsd %s, (sp)\n", pt->reg.name);
    } else if (pt->type == EX_OPER1) {
        compile(pt->oper1.operand);
        printf("\tld t0, (sp)\n");
        printf("\taddi sp, sp, 8\n");
        compile_unary_operation(pt);
    } else if (pt->type == EX_OPER2) {
        compile(pt->oper2.left);
        compile(pt->oper2.right);
        printf("\tld t1, (sp)\n");
        printf("\taddi sp, sp, 8\n");
        printf("\tld t0, (sp)\n");
        printf("\taddi sp, sp, 8\n");
        compile_binary_operation(pt);
    }
}

void compile_output_main(char* name) {
    int fd;
    char c;
    int rv;

    fd = open(name, O_RDONLY);
    while (true) {
        rv = read(fd, &c, 1);
        if (rv <= 0) {
            break;
        }
        printf("%c", c);
    }
}

