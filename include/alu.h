#ifndef ALU_H
#define ALU_H

#include "operand.h"


void handle_add_fn(void* source1, void* source2, OperandFormat* out);
void handle_addu_fn(void* source1, void* source2, OperandFormat* out);
void handle_addf_fn(void* source1, void* source2, OperandFormat* out);
void handle_addv_fn(void* source1, void* source2, OperandFormat* out);
void handle_sub_fn(void* source1, void* source2, OperandFormat* out);
void handle_subu_fn(void* source1, void* source2, OperandFormat* out);
void handle_subf_fn(void* source1, void* source2, OperandFormat* out);
void handle_subv_fn(void* source1, void* source2, OperandFormat* out);
void handle_mul_fn(void* source1, void* source2, OperandFormat* out);
void handle_mulu_fn(void* source1, void* source2, OperandFormat* out);
void handle_mulf_fn(void* source1, void* source2, OperandFormat* out);
void handle_mulv_fn(void* source1, void* source2, OperandFormat* out);
void handle_div_fn(void* source1, void* source2, OperandFormat* out);
void handle_divu_fn(void* source1, void* source2, OperandFormat* out);
void handle_divf_fn(void* source1, void* source2, OperandFormat* out);
void handle_divv_fn(void* source1, void* source2, OperandFormat* out);
void handle_mod_fn(void* source1, void* source2, OperandFormat* out);
void handle_modu_fn(void* source1, void* source2, OperandFormat* out);
void handle_modf_fn(void* source1, void* source2, OperandFormat* out);
void handle_modv_fn(void* source1, void* source2, OperandFormat* out);
void handle_and_fn(void* source1, void* source2, OperandFormat* out);
void handle_or_fn(void* source1, void* source2, OperandFormat* out);
void handle_xor_fn(void* source1, void* source2, OperandFormat* out);
void handle_nand_fn(void* source1, void* source2, OperandFormat* out);
void handle_shr_fn(void* source1, void* source2, OperandFormat* out);
void handle_shl_fn(void* source1, void* source2, OperandFormat* out);
void handle_shll_fn(void* source1, void* source2, OperandFormat* out);
void handle_ror_fn(void* source1, void* source2, OperandFormat* out);
void handle_beq_fn(void* source1, void* source2, OperandFormat* out);
void handle_bne_fn(void* source1, void* source2, OperandFormat* out);
void handle_bge_fn(void* source1, void* source2, OperandFormat* out);
void handle_ble_fn(void* source1, void* source2, OperandFormat* out);
void handle_addi_fn(void* source1, void* source2, OperandFormat* out);
void handle_addiu_fn(void* source1, void* source2, OperandFormat* out);
void handle_addif_fn(void* source1, void* source2, OperandFormat* out);
void handle_addiv_fn(void* source1, void* source2, OperandFormat* out);
void handle_subi_fn(void* source1, void* source2, OperandFormat* out);
void handle_subiu_fn(void* source1, void* source2, OperandFormat* out);
void handle_muli_fn(void* source1, void* source2, OperandFormat* out);
void handle_muliu_fn(void* source1, void* source2, OperandFormat* out);
void handle_mulif_fn(void* source1, void* source2, OperandFormat* out);



#endif 
