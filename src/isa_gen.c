#include "isa_gen.h" 
#include "svec.h" 

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
	.usesWb = true,
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
	.usesWb = true,
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
	.usesWb = true,
	.source = {SOURCE_RB_F, SOURCE_RA_I},
};

static const InstructionInfo ADDV_Instruction = { 
	.opcode = 0,
	.size = 3,
	.inputOperandSize = 2,
	.usesSize = true,
	.alu_fn = handle_addv_fn,
	.move_fn = NULL,
	.usesMove = false,
	.usesExe = true,
	.branch = false,
	.usesWb = true,
	.source = {SOURCE_RB_VECTOR, SOURCE_RA_VECTOR},
};

static const InstructionInfo SUB_Instruction = { 
	.opcode = 1,
	.size = 0,
	.inputOperandSize = 2,
	.usesSize = true,
	.alu_fn = handle_sub_fn,
	.move_fn = NULL,
	.usesMove = false,
	.usesExe = true,
	.branch = false,
	.usesWb = true,
	.source = {SOURCE_RB_I, SOURCE_RA_I},
};

static const InstructionInfo SUBU_Instruction = { 
	.opcode = 1,
	.size = 1,
	.inputOperandSize = 2,
	.usesSize = true,
	.alu_fn = handle_subu_fn,
	.move_fn = NULL,
	.usesMove = false,
	.usesExe = true,
	.branch = false,
	.usesWb = true,
	.source = {SOURCE_RB_I, SOURCE_RA_I},
};

static const InstructionInfo SUBF_Instruction = { 
	.opcode = 1,
	.size = 2,
	.inputOperandSize = 2,
	.usesSize = true,
	.alu_fn = handle_subf_fn,
	.move_fn = NULL,
	.usesMove = false,
	.usesExe = true,
	.branch = false,
	.usesWb = true,
	.source = {SOURCE_RB_F, SOURCE_RA_F},
};

static const InstructionInfo SUBV_Instruction = { 
	.opcode = 1,
	.size = 3,
	.inputOperandSize = 2,
	.usesSize = true,
	.alu_fn = handle_subv_fn,
	.move_fn = NULL,
	.usesMove = false,
	.usesExe = true,
	.branch = false,
	.usesWb = true,
	.source = {SOURCE_RB_VECTOR, SOURCE_RA_VECTOR},
};

static const InstructionInfo MUL_Instruction = { 
	.opcode = 2,
	.size = 0,
	.inputOperandSize = 2,
	.usesSize = true,
	.alu_fn = handle_mul_fn,
	.move_fn = NULL,
	.usesMove = false,
	.usesExe = true,
	.branch = false,
	.usesWb = true,
	.source = {SOURCE_RB_I, SOURCE_RA_I},
};

static const InstructionInfo MULU_Instruction = { 
	.opcode = 2,
	.size = 1,
	.inputOperandSize = 2,
	.usesSize = true,
	.alu_fn = handle_mulu_fn,
	.move_fn = NULL,
	.usesMove = false,
	.usesExe = true,
	.branch = false,
	.usesWb = true,
	.source = {SOURCE_RB_I, SOURCE_RA_I},
};

static const InstructionInfo MULF_Instruction = { 
	.opcode = 2,
	.size = 2,
	.inputOperandSize = 2,
	.usesSize = true,
	.alu_fn = handle_mulf_fn,
	.move_fn = NULL,
	.usesMove = false,
	.usesExe = true,
	.branch = false,
	.usesWb = true,
	.source = {SOURCE_RB_F, SOURCE_RA_F},
};

static const InstructionInfo MULV_Instruction = { 
	.opcode = 2,
	.size = 3,
	.inputOperandSize = 2,
	.usesSize = true,
	.alu_fn = handle_mulv_fn,
	.move_fn = NULL,
	.usesMove = false,
	.usesExe = true,
	.branch = false,
	.usesWb = true,
	.source = {SOURCE_RB_VECTOR, SOURCE_RA_VECTOR},
};

static const InstructionInfo DIV_Instruction = { 
	.opcode = 3,
	.size = 0,
	.inputOperandSize = 2,
	.usesSize = true,
	.alu_fn = handle_div_fn,
	.move_fn = NULL,
	.usesMove = false,
	.usesExe = true,
	.branch = false,
	.usesWb = true,
	.source = {SOURCE_RB_I, SOURCE_RA_I},
};

static const InstructionInfo DIVU_Instruction = { 
	.opcode = 3,
	.size = 1,
	.inputOperandSize = 2,
	.usesSize = true,
	.alu_fn = handle_divu_fn,
	.move_fn = NULL,
	.usesMove = false,
	.usesExe = true,
	.branch = false,
	.usesWb = true,
	.source = {SOURCE_RB_I, SOURCE_RA_I},
};

static const InstructionInfo DIVF_Instruction = { 
	.opcode = 3,
	.size = 2,
	.inputOperandSize = 2,
	.usesSize = true,
	.alu_fn = handle_divf_fn,
	.move_fn = NULL,
	.usesMove = false,
	.usesExe = true,
	.branch = false,
	.usesWb = true,
	.source = {SOURCE_RB_F, SOURCE_RA_F},
};

static const InstructionInfo DIVV_Instruction = { 
	.opcode = 3,
	.size = 3,
	.inputOperandSize = 2,
	.usesSize = true,
	.alu_fn = handle_divv_fn,
	.move_fn = NULL,
	.usesMove = false,
	.usesExe = true,
	.branch = false,
	.usesWb = true,
	.source = {SOURCE_RB_VECTOR, SOURCE_RA_VECTOR},
};

static const InstructionInfo MOD_Instruction = { 
	.opcode = 4,
	.size = 0,
	.inputOperandSize = 2,
	.usesSize = true,
	.alu_fn = handle_mod_fn,
	.move_fn = NULL,
	.usesMove = false,
	.usesExe = true,
	.branch = false,
	.usesWb = true,
	.source = {SOURCE_RB_I, SOURCE_RA_I},
};

static const InstructionInfo MODU_Instruction = { 
	.opcode = 4,
	.size = 1,
	.inputOperandSize = 2,
	.usesSize = true,
	.alu_fn = handle_modu_fn,
	.move_fn = NULL,
	.usesMove = false,
	.usesExe = true,
	.branch = false,
	.usesWb = true,
	.source = {SOURCE_RB_I, SOURCE_RA_I},
};

static const InstructionInfo MODF_Instruction = { 
	.opcode = 4,
	.size = 2,
	.inputOperandSize = 2,
	.usesSize = true,
	.alu_fn = handle_modf_fn,
	.move_fn = NULL,
	.usesMove = false,
	.usesExe = true,
	.branch = false,
	.usesWb = true,
	.source = {SOURCE_RB_F, SOURCE_RA_F},
};

static const InstructionInfo MODV_Instruction = { 
	.opcode = 4,
	.size = 3,
	.inputOperandSize = 2,
	.usesSize = true,
	.alu_fn = handle_modv_fn,
	.move_fn = NULL,
	.usesMove = false,
	.usesExe = true,
	.branch = false,
	.usesWb = true,
	.source = {SOURCE_RB_VECTOR, SOURCE_RA_VECTOR},
};

static const InstructionInfo AND_Instruction = { 
	.opcode = 5,
	.size = 0,
	.inputOperandSize = 2,
	.usesSize = true,
	.alu_fn = handle_and_fn,
	.move_fn = NULL,
	.usesMove = false,
	.usesExe = true,
	.branch = false,
	.usesWb = true,
	.source = {SOURCE_RB_I, SOURCE_RA_I},
};

static const InstructionInfo OR_Instruction = { 
	.opcode = 5,
	.size = 1,
	.inputOperandSize = 2,
	.usesSize = true,
	.alu_fn = handle_or_fn,
	.move_fn = NULL,
	.usesMove = false,
	.usesExe = true,
	.branch = false,
	.usesWb = true,
	.source = {SOURCE_RB_I, SOURCE_RA_I},
};

static const InstructionInfo XOR_Instruction = { 
	.opcode = 5,
	.size = 2,
	.inputOperandSize = 2,
	.usesSize = true,
	.alu_fn = handle_xor_fn,
	.move_fn = NULL,
	.usesMove = false,
	.usesExe = true,
	.branch = false,
	.usesWb = true,
	.source = {SOURCE_RB_I, SOURCE_RA_I},
};

static const InstructionInfo NAND_Instruction = { 
	.opcode = 5,
	.size = 3,
	.inputOperandSize = 2,
	.usesSize = true,
	.alu_fn = handle_nand_fn,
	.move_fn = NULL,
	.usesMove = false,
	.usesExe = true,
	.branch = false,
	.usesWb = true,
	.source = {SOURCE_RB_I, SOURCE_RA_I},
};

static const InstructionInfo SHR_Instruction = { 
	.opcode = 6,
	.size = 0,
	.inputOperandSize = 2,
	.usesSize = true,
	.alu_fn = handle_shr_fn,
	.move_fn = NULL,
	.usesMove = false,
	.usesExe = true,
	.branch = false,
	.usesWb = true,
	.source = {SOURCE_RB_I, SOURCE_RA_I},
};

static const InstructionInfo SHL_Instruction = { 
	.opcode = 6,
	.size = 1,
	.inputOperandSize = 2,
	.usesSize = true,
	.alu_fn = handle_shl_fn,
	.move_fn = NULL,
	.usesMove = false,
	.usesExe = true,
	.branch = false,
	.usesWb = true,
	.source = {SOURCE_RB_I, SOURCE_RA_I},
};

static const InstructionInfo SHLL_Instruction = { 
	.opcode = 6,
	.size = 2,
	.inputOperandSize = 2,
	.usesSize = true,
	.alu_fn = handle_shll_fn,
	.move_fn = NULL,
	.usesMove = false,
	.usesExe = true,
	.branch = false,
	.usesWb = true,
	.source = {SOURCE_RB_I, SOURCE_RA_I},
};

static const InstructionInfo ROR_Instruction = { 
	.opcode = 6,
	.size = 3,
	.inputOperandSize = 2,
	.usesSize = true,
	.alu_fn = handle_ror_fn,
	.move_fn = NULL,
	.usesMove = false,
	.usesExe = true,
	.branch = false,
	.usesWb = true,
	.source = {SOURCE_RB_I, SOURCE_RA_I},
};

static const InstructionInfo BEQ_Instruction = { 
	.opcode = 7,
	.size = 0,
	.inputOperandSize = 2,
	.usesSize = true,
	.alu_fn = handle_beq_fn,
	.move_fn = NULL,
	.usesMove = false,
	.usesExe = true,
	.branch = true,
	.usesWb = true,
	.source = {SOURCE_RB_I, SOURCE_RA_I},
};

static const InstructionInfo BNE_Instruction = { 
	.opcode = 7,
	.size = 1,
	.inputOperandSize = 2,
	.usesSize = true,
	.alu_fn = handle_bne_fn,
	.move_fn = NULL,
	.usesMove = false,
	.usesExe = true,
	.branch = true,
	.usesWb = true,
	.source = {SOURCE_RB_I, SOURCE_RA_I},
};

static const InstructionInfo BGE_Instruction = { 
	.opcode = 7,
	.size = 2,
	.inputOperandSize = 2,
	.usesSize = true,
	.alu_fn = handle_bge_fn,
	.move_fn = NULL,
	.usesMove = false,
	.usesExe = true,
	.branch = true,
	.usesWb = true,
	.source = {SOURCE_RB_I, SOURCE_RA_I},
};

static const InstructionInfo BLE_Instruction = { 
	.opcode = 7,
	.size = 3,
	.inputOperandSize = 2,
	.usesSize = true,
	.alu_fn = handle_ble_fn,
	.move_fn = NULL,
	.usesMove = false,
	.usesExe = true,
	.branch = true,
	.usesWb = true,
	.source = {SOURCE_RB_I, SOURCE_RA_I},
};

static const InstructionInfo ADDI_Instruction = { 
	.opcode = 8,
	.size = 0,
	.inputOperandSize = 2,
	.usesSize = true,
	.alu_fn = handle_addi_fn,
	.move_fn = NULL,
	.usesMove = false,
	.usesExe = true,
	.branch = false,
	.usesWb = true,
	.source = {SOURCE_RB_I, SOURCE_CONSTANT},
};

static const InstructionInfo ADDIU_Instruction = { 
	.opcode = 8,
	.size = 1,
	.inputOperandSize = 2,
	.usesSize = true,
	.alu_fn = handle_addiu_fn,
	.move_fn = NULL,
	.usesMove = false,
	.usesExe = true,
	.branch = false,
	.usesWb = true,
	.source = {SOURCE_RB_I, SOURCE_CONSTANT},
};

static const InstructionInfo ADDIF_Instruction = { 
	.opcode = 8,
	.size = 2,
	.inputOperandSize = 2,
	.usesSize = true,
	.alu_fn = handle_addif_fn,
	.move_fn = NULL,
	.usesMove = false,
	.usesExe = true,
	.branch = false,
	.usesWb = true,
	.source = {SOURCE_RB_I, SOURCE_CONSTANT},
};

static const InstructionInfo SUBI_Instruction = { 
	.opcode = 9,
	.size = 0,
	.inputOperandSize = 2,
	.usesSize = true,
	.alu_fn = handle_subi_fn,
	.move_fn = NULL,
	.usesMove = false,
	.usesExe = true,
	.branch = false,
	.usesWb = true,
	.source = {SOURCE_RB_I, SOURCE_CONSTANT},
};

static const InstructionInfo SUBIU_Instruction = { 
	.opcode = 9,
	.size = 1,
	.inputOperandSize = 2,
	.usesSize = true,
	.alu_fn = handle_subiu_fn,
	.move_fn = NULL,
	.usesMove = false,
	.usesExe = true,
	.branch = false,
	.usesWb = true,
	.source = {SOURCE_RB_I, SOURCE_CONSTANT},
};

static const InstructionInfo SUBIF_Instruction = { 
	.opcode = 9,
	.size = 2,
	.inputOperandSize = 2,
	.usesSize = true,
	.alu_fn = handle_subiu_fn,
	.move_fn = NULL,
	.usesMove = false,
	.usesExe = true,
	.branch = false,
	.usesWb = true,
	.source = {SOURCE_RB_I, SOURCE_CONSTANT},
};

static const InstructionInfo MULI_Instruction = { 
	.opcode = 10,
	.size = 0,
	.inputOperandSize = 2,
	.usesSize = true,
	.alu_fn = handle_muli_fn,
	.move_fn = NULL,
	.usesMove = false,
	.usesExe = true,
	.branch = false,
	.usesWb = true,
	.source = {SOURCE_RB_I, SOURCE_CONSTANT},
};

static const InstructionInfo MULIU_Instruction = { 
	.opcode = 10,
	.size = 1,
	.inputOperandSize = 2,
	.usesSize = true,
	.alu_fn = handle_muliu_fn,
	.move_fn = NULL,
	.usesMove = false,
	.usesExe = true,
	.branch = false,
	.usesWb = true,
	.source = {SOURCE_RB_I, SOURCE_CONSTANT},
};

static const InstructionInfo MULIF_Instruction = { 
	.opcode = 10,
	.size = 2,
	.inputOperandSize = 2,
	.usesSize = true,
	.alu_fn = handle_mulif_fn,
	.move_fn = NULL,
	.usesMove = false,
	.usesExe = true,
	.branch = false,
	.usesWb = true,
	.source = {SOURCE_RB_I, SOURCE_CONSTANT},
};

const InstructionInfo* instructionTable[INSTRUCTION_LENGTH][VARIANT_LENGTH] =  {
	[0][0] = &ADD_Instruction,
	[0][1] = &ADDU_Instruction,
	[0][2] = &ADDF_Instruction,
	[0][3] = &ADDV_Instruction,
	[1][0] = &SUB_Instruction,
	[1][1] = &SUBU_Instruction,
	[1][2] = &SUBF_Instruction,
	[1][3] = &SUBV_Instruction,
	[2][0] = &MUL_Instruction,
	[2][1] = &MULU_Instruction,
	[2][2] = &MULF_Instruction,
	[2][3] = &MULV_Instruction,
	[3][0] = &DIV_Instruction,
	[3][1] = &DIVU_Instruction,
	[3][2] = &DIVF_Instruction,
	[3][3] = &DIVV_Instruction,
	[4][0] = &MOD_Instruction,
	[4][1] = &MODU_Instruction,
	[4][2] = &MODF_Instruction,
	[4][3] = &MODV_Instruction,
	[5][0] = &AND_Instruction,
	[5][1] = &OR_Instruction,
	[5][2] = &XOR_Instruction,
	[5][3] = &NAND_Instruction,
	[6][0] = &SHR_Instruction,
	[6][1] = &SHL_Instruction,
	[6][2] = &SHLL_Instruction,
	[6][3] = &ROR_Instruction,
	[7][0] = &BEQ_Instruction,
	[7][1] = &BNE_Instruction,
	[7][2] = &BGE_Instruction,
	[7][3] = &BLE_Instruction,
	[8][0] = &ADDI_Instruction,
	[8][1] = &ADDIU_Instruction,
	[8][2] = &ADDIF_Instruction,
	[9][0] = &SUBI_Instruction,
	[9][1] = &SUBIU_Instruction,
	[9][2] = &SUBIF_Instruction,
	[10][0] = &MULI_Instruction,
	[10][1] = &MULIU_Instruction,
	[10][2] = &MULIF_Instruction,
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
    