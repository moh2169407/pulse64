#ifndef REGISTER_H
#define REGISTER_H

#include <stdint.h>

#define REGISTER_SIZE 32

typedef struct {
    uint64_t regInt[REGISTER_SIZE];
    uint64_t pc;
    uint64_t ir;
    double regFloat[REGISTER_SIZE];
} Registers;

// Create and free registers
Registers* pulse_registers_init();

void pulse_registers_free(Registers* registers);

// Setting int registers values 
void pulse_registers_int_set(Registers* registers, int8_t index, int64_t data);

// Gets int register value
int64_t pulse_register_int_get(Registers* registers, int8_t index);

// Getting int register value by address
uint64_t* pulse_register_int_get_adrs(Registers* registers, int8_t index);



// Getting double register values
double pulse_register_float_get(Registers* registers, int index);

// Gets the double value by address
double* pulse_register_float_get_adrs(Registers* registers, int index);

void pulse_register_float_set(Registers* registers, int index, double val);



int64_t pulse_register_get_pc(Registers* registers);

void pulse_register_set_pc(Registers* registers, int64_t data);

int64_t pulse_register_get_ir(Registers* registers);

void pulse_register_set_ir(Registers* registers, uint64_t data);

#endif
