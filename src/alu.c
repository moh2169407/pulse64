#include "alu.h"
#include <stdint.h>

#include <math.h>
#include "operand.h"

void handle_add_fn(void* source1, void* source2, OperandFormat* out){
    int64_t input1 = *(int64_t*) source1;
    int64_t input2 = *(int64_t*) source2;
    
    *(int64_t*)out->data = input1 + input2;
    out->type = OPERAND_REGISTER_I;
}
void handle_addu_fn(void* source1, void* source2, OperandFormat* out){
    uint64_t input1 = *(uint64_t*) source1;
    uint64_t input2 = *(uint64_t*) source2;

    *(uint64_t*)out->data = input1 + input2;
    out->type = OPERAND_REGISTER_I;
}
void handle_addf_fn(void* source1, void* source2, OperandFormat* out){
    double input1 = *(double*) source1;
    double input2 = *(double*) source2;

    *(double*)out->data = input1 + input2;
    out->type = OPERAND_REGISTER_F;
}
void handle_addv_fn(void* source1, void* source2, OperandFormat* out){
    int64_t* input1 = (int64_t*) source1;
    int64_t* input2 = (int64_t*) source2;
    for (int i = 0; i < 5; i++) {
       ((int64_t*)out->data)[i] =  input1[i] + input2[i];
    }
    out->type = OPERAND_VECTOR;
}
void handle_sub_fn(void* source1, void* source2, OperandFormat* out){
    int64_t input1 = *(int64_t*) source1;
    int64_t input2 = *(int64_t*) source2;
    
    *(int64_t*)out->data = input1 - input2;
    out->type = OPERAND_REGISTER_I;
}
void handle_subu_fn(void* source1, void* source2, OperandFormat* out){
    uint64_t input1 = *(uint64_t*) source1;
    uint64_t input2 = *(uint64_t*) source2;

    *(int64_t*)out->data = input1 - input2;
    out->type = OPERAND_REGISTER_I;
}
void handle_subf_fn(void* source1, void* source2, OperandFormat* out){
    double input1 = *(double*) source1;
    double input2 = *(double*) source2;

    *(double*)out->data = input1 - input2;
    out->type = OPERAND_REGISTER_F;
}
void handle_subv_fn(void* source1, void* source2, OperandFormat* out){
    int64_t* input1 = (int64_t*) source1;
    int64_t* input2 = (int64_t*) source2;
    for (int i = 0; i < 5; i++) {
       ((int64_t*)out->data)[i] =  input1[i] - input2[i];
    }
    out->type = OPERAND_VECTOR;
}
void handle_mul_fn(void* source1, void* source2, OperandFormat* out){
    int64_t input1 = *(int64_t*) source1;
    int64_t input2 = *(int64_t*) source2;
    
    *(int64_t*)out->data = input1 * input2;
    out->type = OPERAND_REGISTER_I;
}
void handle_mulu_fn(void* source1, void* source2, OperandFormat* out){
    uint64_t input1 = *(uint64_t*) source1;
    uint64_t input2 = *(uint64_t*) source2;

    *(int64_t*)out->data = input1 * input2;
    out->type = OPERAND_REGISTER_I;
}
void handle_mulf_fn(void* source1, void* source2, OperandFormat* out){
    double input1 = *(double*) source1;
    double input2 = *(double*) source2;

    *(double*)out->data = input1 * input2;
    out->type = OPERAND_REGISTER_F;
}
void handle_mulv_fn(void* source1, void* source2, OperandFormat* out){
    int64_t* input1 = (int64_t*) source1;
    int64_t* input2 = (int64_t*) source2;
    for (int i = 0; i < 5; i++) {
       ((int64_t*)out->data)[i] =  input1[i] - input2[i];
    }
    out->type = OPERAND_VECTOR;
}
void handle_div_fn(void* source1, void* source2, OperandFormat* out){
    int64_t input1 = *(int64_t*) source1;
    int64_t input2 = *(int64_t*) source2;
    
    *(int64_t*)out->data = input1 / input2;
    out->type = OPERAND_REGISTER_I;
}
void handle_divu_fn(void* source1, void* source2, OperandFormat* out){
    uint64_t input1 = *(uint64_t*) source1;
    uint64_t input2 = *(uint64_t*) source2;

    *(int64_t*)out->data = input1 / input2;
    out->type = OPERAND_REGISTER_I;
}
void handle_divf_fn(void* source1, void* source2, OperandFormat* out){
    double input1 = *(double*) source1;
    double input2 = *(double*) source2;
    
    *(double*)out->data = input1 / input2;
    out->type = OPERAND_REGISTER_I;
}
void handle_divv_fn(void* source1, void* source2, OperandFormat* out){
    int64_t* input1 = (int64_t*) source1;
    int64_t* input2 = (int64_t*) source2;
    for (int i = 0; i < 5; i++) {
       ((int64_t*)out->data)[i] =  input1[i] / input2[i];
    }
    out->type = OPERAND_VECTOR;
}
void handle_mod_fn(void* source1, void* source2, OperandFormat* out){
    int64_t input1 = *(int64_t*) source1;
    int64_t input2 = *(int64_t*) source2;
    
    *(int64_t*)out->data = input1 % input2;
    out->type = OPERAND_REGISTER_I;
}
void handle_modu_fn(void* source1, void* source2, OperandFormat* out){
    uint64_t input1 = *(uint64_t*) source1;
    uint64_t input2 = *(uint64_t*) source2;

    *(int64_t*)out->data = input1 % input2;
    out->type = OPERAND_REGISTER_I;
}
void handle_modf_fn(void* source1, void* source2, OperandFormat* out){
    double input1 = *(double*) source1;
    double input2 = *(double*) source2;
    
    *(double*)out->data = fmod(input1, input2);
    out->type = OPERAND_REGISTER_I;
}
void handle_modv_fn(void* source1, void* source2, OperandFormat* out){
    int64_t* input1 = (int64_t*) source1;
    int64_t* input2 = (int64_t*) source2;
    for (int i = 0; i < 5; i++) {
       ((int64_t*)out->data)[i] =  input1[i] % input2[i];
    }
    out->type = OPERAND_VECTOR;
}
void handle_and_fn(void* source1, void* source2, OperandFormat* out){
    int64_t input1 = *(int64_t*) source1;
    int64_t input2 = *(int64_t*) source2;
    
    *(int64_t*)out->data = input1 & input2;
    out->type = OPERAND_REGISTER_I;
}
void handle_or_fn(void* source1, void* source2, OperandFormat* out){
    int64_t input1 = *(int64_t*) source1;
    int64_t input2 = *(int64_t*) source2;
    
    *(int64_t*)out->data = input1 | input2;
    out->type = OPERAND_REGISTER_I;
}
void handle_xor_fn(void* source1, void* source2, OperandFormat* out){
    int64_t input1 = *(int64_t*) source1;
    int64_t input2 = *(int64_t*) source2;
    
    *(int64_t*)out->data = input1 ^ input2;
    out->type = OPERAND_REGISTER_I;
}
void handle_nand_fn(void* source1, void* source2, OperandFormat* out){
    int64_t input1 = *(int64_t*) source1;
    int64_t input2 = *(int64_t*) source2;
    
    *(int64_t*)out->data = ~(input1 & input2);
    out->type = OPERAND_REGISTER_I;
}
void handle_shr_fn(void* source1, void* source2, OperandFormat* out){
    int64_t input1 = *(int64_t*) source1;
    int64_t input2 = *(int64_t*) source2;
    
    *(int64_t*)out->data = input1 >> input2;
    out->type = OPERAND_REGISTER_I;
}
void handle_shl_fn(void* source1, void* source2, OperandFormat* out){
    int64_t input1 = *(int64_t*) source1;
    int64_t input2 = *(int64_t*) source2;
    
    *(int64_t*)out->data = input1 << input2;
    out->type = OPERAND_REGISTER_I;
}
void handle_shll_fn(void* source1, void* source2, OperandFormat* out){

}
void handle_ror_fn(void* source1, void* source2, OperandFormat* out){}
void handle_beq_fn(void* source1, void* source2, OperandFormat* out){
    int64_t input1 = *(int64_t*) source1;
    int64_t input2 = *(int64_t*) source2;
    int64_t output;
    if (input1 == input2) {
        output = 1;
    }
    else {
        output = 0;
    }
    *(int64_t*)out->data = output;
    out->type = OPERAND_REGISTER_I;
}
void handle_bne_fn(void* source1, void* source2, OperandFormat* out){
    int64_t input1 = *(int64_t*) source1;
    int64_t input2 = *(int64_t*) source2;
    int64_t output;
    if (input1 != input2) {
        output = 1;
    }
    else {
        output = 0;
    }
    *(int64_t*)out->data = output;
    out->type = OPERAND_REGISTER_I;
}
void handle_bge_fn(void* source1, void* source2, OperandFormat* out){
    int64_t input1 = *(int64_t*) source1;
    int64_t input2 = *(int64_t*) source2;
    int64_t output;
    if (input1 >= input2) {
        output = 1;
    }
    else {
        output = 0;
    }
    *(int64_t*)out->data = output;
    out->type = OPERAND_REGISTER_I;
}
void handle_ble_fn(void* source1, void* source2, OperandFormat* out){
    int64_t input1 = *(int64_t*) source1;
    int64_t input2 = *(int64_t*) source2;
    int64_t output;
    if (input1 <= input2) {
        output = 1;
    }
    else {
        output = 0;
    }
    out->type = OPERAND_REGISTER_I;
}
void handle_addi_fn(void* source1, void* source2, OperandFormat* out){
    handle_add_fn(source1, source2, out);
}
void handle_addiu_fn(void* source1, void* source2, OperandFormat* out){
    handle_addu_fn(source1, source2, out);
}
void handle_addif_fn(void* source1, void* source2, OperandFormat* out){
    handle_addf_fn(source1, source2, out);
}
void handle_subi_fn(void* source1, void* source2, OperandFormat* out) {
    handle_sub_fn(source1, source2, out);
}
void handle_subiu_fn(void* source1, void* source2, OperandFormat* out) {
    handle_subu_fn(source1, source2, out);
}
void handle_muli_fn(void* source1, void* source2, OperandFormat* out) {
    handle_mul_fn(source1, source2, out);
}
void handle_muliu_fn(void* source1, void* source2, OperandFormat* out) {
    handle_mulu_fn(source1, source2, out);
}

void handle_mulif_fn(void* source1, void* source2, OperandFormat* out) {
    handle_mulf_fn(source1, source2, out);
}

