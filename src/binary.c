#include <stdio.h>
#include "binary.h"
#include "codInterm.h"
#include <assembly.h>


unsigned int get_opcode(char * name, instruction_type_t type){
    int opcode = -1;

    if (type == typeR) {
        opcode = 0b000000;
    } else if (!strcmp(name, "lw")) {
        opcode = 0b000101; 
    } else if (!strcmp(name, "sw")) {
        opcode = 0b000111;
    } else if (!strcmp(name, "addi")){
        opcode = 0b000001;
    } else if (!strcmp(name, "subi")){
        opcode = 0b000010;
    } else if (!strcmp(name, "andi")) {
        opcode = 0b000011;
    } else if (!strcmp(name, "ori")) {
        opcode = 0b000100;
    } else if (!strcmp(name, "beq")) {
        opcode = 0b001110;
    } else if (!strcmp(name, "bne")) {
        opcode = 0b001111;
    } else if (!strcmp(name, "slti")) {
        opcode = 0b001101;
    } else if (!strcmp(name, "in")) {
        opcode = 0b001011;
    } else if (!strcmp(name, "out")) {
        opcode = 0b001100;
    }else if (!strcmp(name, "j")) {
        opcode = 0b001000;
    } else if (!strcmp(name, "jal")) {
        opcode = 0b001010;
    } else if (!strcmp(name, "halt")){
        opcode = 0b111111;
    } else if (!strcmp(name, "xori")){
        opcode = 0b010010;
    }
    return opcode;
}


unsigned int get_funct(char * name){
    int funct = -1;

    if (!strcmp(name, "add")) {
        funct = 0b000001;
    } else if (!strcmp(name, "sub")) {
        funct = 0b000010;
    } else if (!strcmp(name, "mult")) {
        funct = 0b000100;
    } else if (!strcmp(name, "div")) {
        funct = 0b000011;
    } else if (!strcmp(name, "and")) {
        funct = 0b000101;
    } else if (!strcmp(name, "or")) {
        funct = 0b000110;
    } else if (!strcmp(name, "xor")) {
        funct = 0b010000;
    } else if (!strcmp(name, "sll")) {
        funct = 0b001000;
    } else if (!strcmp(name, "srl")) {
        funct = 0b001001;
    } else if (!strcmp(name, "jr")) {
        funct = 0b001010;
    } else if (!strcmp(name, "jalr")) {
        funct = 0b001011;
    } else if (!strcmp(name, "slt")){
        funct = 0b001100;
    }
    return funct;
}

unsigned int get_register(int reg){
    return reg;
}

unsigned int get_shamt(int shamt){
    return shamt;
}

unsigned int get_immediate(int immediate){
    return immediate;
}

unsigned int get_address(char* label){
    return 0; // TODO Label Adress
}

BIN_R* binaryR(ASSEMBLY* instruction){
    BIN_R* bin = (BIN_R*) malloc(sizeof(BIN_R));
    bin->opcode = get_opcode(instruction->type_r->nome, instruction->type);
    bin->rs = get_register(instruction->type_r->rs);
    bin->rt = get_register(instruction->type_r->rt);
    bin->rd = get_register(instruction->type_r->rd);
    bin->shamt = get_shamt(instruction->type_r->shamt);
    bin->funct = get_funct(instruction->type_r->nome);
    return bin;
}

BIN_I* binaryI(ASSEMBLY* instruction){
    BIN_I* bin = (BIN_I*) malloc(sizeof(BIN_I));
    bin->opcode = get_opcode(instruction->type_i->nome, instruction->type);
    bin->rs = get_register(instruction->type_i->rs);
    bin->rt = get_register(instruction->type_i->rt);
    bin->immediate = get_immediate(instruction->type_i->imediate); // TODO BEQ e BNE
    return bin;
}

BIN_J* binaryJ(ASSEMBLY* instruction){
    BIN_J* bin = (BIN_J*) malloc(sizeof(BIN_J));
    bin->opcode = get_opcode(instruction->type_j->nome, instruction->type);
    bin->address = get_address(instruction->type_j->labelImediate); // TODO Label Adress
    return bin;
}