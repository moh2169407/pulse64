#include "isa_gen.h" 
#include "../../svec/svec.h" 

static const InstructionInfo ADD_Instruction = { 
	.opcode = 0,
	.size = 0,
	.inputOperandSize = 2,
	.usesSize = true,
	.alu_fn = handle_add_fn,
	.move_fn = NULL,
	.usesMove = false,
	.usesExe = true,
	.branch = false,
	.source = {SOURCE_RB_I, SOURCE_RA_I},
};

static const InstructionInfo ADDU_Instruction = { 
	.opcode = 0,
	.size = 1,
	.inputOperandSize = 2,
	.usesSize = true,
	.alu_fn = handle_addu_fn,
	.move_fn = NULL,
	.usesMove = false,
	.usesExe = true,
	.branch = false,
	.source = {SOURCE_RB_I, SOURCE_RA_I},
};

static const InstructionInfo ADDF_Instruction = { 
	.opcode = 0,
	.size = 2,
	.inputOperandSize = 2,
	.usesSize = true,
	.alu_fn = handle_addf_fn,
	.move_fn = NULL,
	.usesMove = false,
	.usesExe = true,
	.branch = false,
	.source = {SOURCE_RB_F, SOURCE_RA_I},
};

const InstructionInfo* instructionTable[INSTRUCTION_LENGTH][VARIANT_LENGTH] =  {
	[0][0] = &ADD_Instruction,
	[1][1] = &ADDU_Instruction,
	[2][2] = &ADDF_Instruction,
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
    
InstructionInstance* pulse_isa_init_instruction_instance(int size) {
    InstructionInstance* instance = xmalloc(sizeof(*instance));
    instance->opformat  = xmalloc(sizeof(*instance->opformat) * size);

    instance->output = xmalloc(sizeof(*instance->output));
    instance->output->data = xmalloc(sizeof(uint64_t));
    return instance;
}
    
void pulse_isa_free_instruction_instance(InstructionInstance* instance) {
    free(instance->opformat);
    free(instance->output->data);
    free(instance->output);
    free(instance);
}
    