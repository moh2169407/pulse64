#include "register.h"

#include "../../svec/svec.h"

union DataSwap {
    uint64_t word;
    uint32_t half;
    uint16_t hhalf;
    uint8_t byte[8];
};

Registers* pulse_registers_init() {
    Registers* reg = xmalloc(sizeof(*reg));
    return reg;
}

void pulse_registers_free(Registers* registers) {
    free(registers);
}

void pulse_registers_int_set(Registers* registers, int8_t index, int64_t data) {
    if (index < 0 || index > REGISTER_SIZE) {
        // TODO signals
    }
    registers->regInt[index] = data;
}

int64_t pulse_register_int_get(Registers* registers, int8_t index) {
    if (index < 0 || index > REGISTER_SIZE) {
        // TODO Signals 
    }
    return registers->regInt[index];
}

uint64_t* pulse_register_int_get_adrs(Registers* registers, int8_t index) {
    if (index < 0 || index > REGISTER_SIZE) {
        // TODO Signals 
    }
    return &registers->regInt[index];
}

int64_t pulse_register_get_pc(Registers* registers) {
    return registers->pc;
}

void pulse_register_set_pc(Registers* registers, int64_t data) {
    registers->pc = data;
}

int64_t pulse_register_get_ir(Registers* registers) {
    return registers->ir;
}

void pulse_register_set_ir(Registers* registers, uint64_t data) {
    registers->ir = data;
} 



