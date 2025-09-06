#ifndef OPERAND_H
#define OPERAND_H

typedef enum {
    OPERAND_NONE = 0,
    OPERAND_REGISTER_I,
    OPERAND_REGISTER_F,
    OPERAND_CONSTANT,
    OPERAND_MEM
} OperandType;

typedef struct {
    void* data; 
    OperandType type;  
} OperandFormat;


#endif
