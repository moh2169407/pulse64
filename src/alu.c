#include "alu.h"
#include "isa_gen.h"

#include "operand.h"


void handle_add_fn(void* source1, void* source2, OperandFormat* operand) {
    int64_t input1 = *(int64_t*)source1; 
    int64_t input2 = *(int64_t*)source2; 
    int64_t outPut = input1 + input2;

    *(int64_t*)operand->data = outPut;

    operand->type = OPERAND_REGISTER_I;
}

void handle_addu_fn(void* ss , void* a, OperandFormat* operand) {

}

void handle_addf_fn(void* ss , void* a, OperandFormat* operand) {

}

