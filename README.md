# RISC-V Assembly and NTLang Code Generation

## Overview
This project involves writing RISC-V Assembly code to handle string and integer data and building a simple compiler for NTLang expressions. The goal is to develop a deeper understanding of low-level programming and compiler construction.

## RISC-V Assembly Program

### Requirements
- Develop RISC-V assembly language implementations for the specified problems.
- Ensure the logic follows the provided C code examples.
- Use a Makefile for compilation.
- Follow RISC-V function calling conventions.

### Implemented programs
- `rstr`: Reverse a string.
- `rstr_rec`: Reverse a string recursively.
- `pack_bytes`: Combine four 1-byte values into a 32-bit signed integer.
- `unpack_bytes`: Unpack a 32-bit signed integer into four 1-byte unsigned values.
- `get_bitseq`: Extract a sequence of bits from an unsigned integer.
- `get_bitseq_signed`: Extract a sequence of bits from an unsigned integer and return as a signed integer.

## NTLang Code Generation

### Enhancements
- Add parameter support to NTLang to allow expressions with variables.
- Implement a compiler mode that generates RISC-V assembly code from NTLang expressions.

### Usage
Compile NTLang expressions into RISC-V assembly:

```bash
./ntlang −e "(a0+a1)∗a2" −c foo > foo.s gcc -o foo foo.s
./foo 3 4 5
```

### Code Generation
- Output a preamble in assembly that parses arguments.
- Generate stack machine code from the parse tree.

## Building and Running

### Makefile
Use the provided Makefile to compile the RISC-V assembly programs and the NTLang compiler.

### Testing
Ensure that both the C implementation and your RISC-V implementation compute the correct answer.


## Acknowledgments
- Professor Gregory Benson for providing the project framework.
- The RISC-V community for resources and support.