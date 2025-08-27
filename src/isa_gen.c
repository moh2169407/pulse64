#include "isa_gen.h"
#include "../../svec/svec.h"
static const InstructionInfo ADD_Instruction = {
    .opcode = 1,
    .size = 0,
    .usesSize = true,
    .format = {OPERAND_REGISTER_I, OPERAND_REGISTER_I},
    // .operandSize = 2,
    //
    // .usesExe = true,
    .handler_fn = handle_add_fn
};

static const InstructionInfo ADDU_Instruction = {
    .opcode = 0,
    .size = 1,
    .usesSize = true,
    .format = {OPERAND_REGISTER_I, OPERAND_REGISTER_I},
    .handler_fn = handle_addu_fn,
};


const InstructionInfo* instructionTable[INSTRUCTION_LENGTH][VARIANT_LENGTH] =  {
    [0][0] = &ADD_Instruction,
    [0][1] = &ADDU_Instruction,
};

const InstructionInfo* pulse_isa_get_instruction_info(uint8_t opcode, uint8_t size) {
   const InstructionInfo* info = instructionTable[opcode][0];
    if (!info) {
        return NULL;
    }
    if (info->usesSize) {
        const InstructionInfo* userInfo =  instructionTable[opcode][size];
        return userInfo ? userInfo : NULL;
    }
    return info;
}
