#ifndef REGISTER_H
#define REGISTER_H

#include <stdint.h>

#define REGISTER_SIZE 32

#define VECTOR_SIZE 5
#define SPEICAL_REGISTER_NUM 3


#define REG_REGISTER_INT_END 20
#define REG_REGISTER8_END    23
#define REG_REGISTER16_END   26
#define REG_REGISTER32_END   29
#define VECTOR_REGISTER_END  32

typedef struct {

    union {
        uint64_t reg64;
        uint32_t reg32;
        uint16_t reg16;
        uint8_t reg8;
        double f64;
        uint64_t vec[VECTOR_SIZE];
};
} RegisterValue;

typedef enum {
    REGISTER64,
    REGISTER32,
    REGISTER16,
    REGISTER8,
    REGISTER_FLOAT64,
    REGISTER_VECTOR,
} RegisterType;

typedef struct {
    RegisterValue val;
    RegisterType type;
}Registers;

typedef struct {
    Registers regInt[32]; 
    double regFloat[32];
    uint64_t pc;
    uint64_t ir;
} RegisterFile;

// Create and free registers
RegisterFile* pulse_registers_init();

void pulse_registers_free(RegisterFile* registers);

// Setting int registers values 
void pulse_registers_int_set(RegisterFile* registers, int8_t index, int64_t data);

// Gets int register value
int64_t pulse_register_int_get(RegisterFile* registers, int8_t index);

// Getting int register value by address
uint64_t* pulse_register_int_get_adrs(RegisterFile* registers, int8_t index);



// Getting double register values
double pulse_register_double_get(RegisterFile* registers, int index);

// Gets the double value by address
double* pulse_register_double_get_adrs(RegisterFile* registers, int index);

void pulse_register_double_set(RegisterFile* registers, int index, double val);



int64_t pulse_register_get_pc(RegisterFile* registers);

void pulse_register_set_pc(RegisterFile* registers, int64_t data);

int64_t pulse_register_get_ir(RegisterFile* registers);

void pulse_register_set_ir(RegisterFile* registers, uint64_t data);

RegisterType pulse_register_get_type(int idx);


int64_t pulse_register_vector_get(RegisterFile* registers, int index, int subIndex);

void pulse_register_vector_set(RegisterFile* registers, int index, int subIndex, int64_t val);
uint64_t* pulse_register_vector_get_adrs(RegisterFile* registers, int index, int subIndex);
#endif
