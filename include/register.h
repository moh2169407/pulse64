#ifndef REGISTER_H
#define REGISTER_H

#include <stdint.h>

#define REGISTER_SIZE 32

typedef struct {
    uint64_t regInt[32];
    uint64_t pc;
    uint64_t ir;

} Registers;

Registers* pulse_registers_init();

void pulse_registers_free(Registers* registers);

void pulse_registers_set(Registers* registers, int8_t index, int64_t data);

int64_t pulse_register_get(Registers* registers, int8_t index);

int64_t pulse_register_get_pc(Registers* registers);

void pulse_register_set_pc(Registers* registers, int64_t data);

int64_t pulse_register_get_ir(Registers* registers);

void pulse_register_set_ir(Registers* registers, uint64_t data);

#endif
