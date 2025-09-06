#ifndef ALU_H
#define ALU_H

#include "operand.h"


void handle_add_fn(void* source1, void* source2, OperandFormat* operand);
void handle_addu_fn(void*, void*, OperandFormat* operand);
void handle_addf_fn(void* ss , void* a, OperandFormat* operand);





#endif 
