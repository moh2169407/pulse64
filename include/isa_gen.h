#ifndef ISA_GEN_H
#define ISA_GEN_H

#include <stdint.h>
#include <stdbool.h>

#include "alu.h"
#include "operand.h"

#define INSTRUCTION_LENGTH 150
#define VARIANT_LENGTH 4

typedef enum {
    SOURCE_NONE = 0,
    SOURCE_RC_I,
    SOURCE_RC_F,
    SOURCE_RB_I,
    SOURCE_RB_F,
    SOURCE_RA_I,
    SOURCE_RA_F,
    SOURCE_CONSTANT,
    SOURCE_RC_VECTOR,
    SOURCE_RB_VECTOR,
    SOURCE_RA_VECTOR,
} Sourcetype;

typedef void (*handler) (void*, void*, OperandFormat*);

typedef struct {
    uint8_t opcode;     /* binary opcode for instruction */
    uint8_t size;       /* the size defines variants for instructions */
    handler alu_fn; /* A function pointer for handling instructions */

    handler move_fn;
    int inputOperandSize;
    Sourcetype source[2];

    bool usesSize;      /* A bool because not every instruction uses variants */
    bool usesExe;       /* Instruction uses the alu and execution stage */
    bool usesMove;      /* Instruction uses the move stage */
    bool usesWb;
    bool usesMem;
    bool branch;
} InstructionInfo;


typedef struct {
    const InstructionInfo* info;
    OperandFormat* opformat;
    OperandFormat* output;
    uint64_t outputIdx;
    bool branchTake;
} InstructionInstance;

const extern InstructionInfo* instructionTable[INSTRUCTION_LENGTH][VARIANT_LENGTH];



const InstructionInfo* pulse_isa_get_instruction_info(uint8_t opcode, uint8_t size);

InstructionInstance* pulse_isa_init_instruction_instance(int size);

void pulse_isa_free_instruction_instance(InstructionInstance* instance);

#endif
