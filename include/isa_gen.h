#ifndef ISA_GEN_H
#define ISA_GEN_H

#include <stdint.h>
#include <stdbool.h>

#include "alu.h"

#define INSTRUCTION_LENGTH 150
#define VARIANT_LENGTH 4

typedef uint64_t (*handler) (uint64_t, uint64_t);

typedef enum {
    OPERAND_NONE = 0,
    OPERAND_REGISTER_I,
    OPERAND_REGISTER_F,
    OPERAND_CONSTANT,
    OPERAND_MEM
} OperandType;

typedef struct {
    uint8_t opcode;     /* binary opcode for instruction */
    uint8_t size;       /* the size defines variants for instructions */
    handler handler_fn; /* A function pointer for handling instructions */
    bool usesSize;      /* A bool because not every instruction uses variants */
    OperandType format[2];
} InstructionInfo;

typedef struct {
    const InstructionInfo* info;
    uint64_t inputI[2];
    double inputF[2];
    uint64_t output;
} InstructionInstance;

const extern InstructionInfo* instructionTable[INSTRUCTION_LENGTH][VARIANT_LENGTH];


const InstructionInfo* pulse_isa_get_instruction_info(uint8_t opcode, uint8_t size);


#endif
