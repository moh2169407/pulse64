#include "log.h"
#include "register.h"

#include "../../svec/svec.h"

RegisterFile* pulse_registers_init() {
    RegisterFile* regFile = xmalloc(sizeof(*regFile));
    regFile->ir = 0;
    regFile->pc = 0;

    for (int i = 0; i < REGISTER_SIZE; i++) {
        if (i < REG_REGISTER_INT_END) {
            regFile->regInt[i].val.reg64 = 0;
            regFile->regInt[i].type = REGISTER32;
        }
        else if (i < REG_REGISTER8_END) {
            regFile->regInt[i].val.reg8 = 0;
            regFile->regInt[i].type = REGISTER8;
        }
        else if (i < REG_REGISTER16_END) {
            regFile->regInt[i].val.reg16 = 0;
            regFile->regInt[i].type = REGISTER16;
        }
        else if (i < REG_REGISTER32_END) {
            regFile->regInt[i].val.reg32 = 0;
            regFile->regInt[i].type = REGISTER32;
        }
        else if (i < VECTOR_REGISTER_END) {
            regFile->regInt[i].val.vec[0] = 0;
            regFile->regInt[i].val.vec[1] = 0;
            regFile->regInt[i].val.vec[2] = 0;
            regFile->regInt[i].val.vec[3] = 0;
            regFile->regInt[i].val.vec[4] = 0;
            regFile->regInt[i].type = REGISTER_VECTOR;
        }
    }
    return regFile;
}

void pulse_registers_free(RegisterFile* registers) {
    free(registers);
}

void pulse_registers_int_set(RegisterFile* registers, int8_t index, int64_t data) {
    if (index < 0 || index > REGISTER_SIZE) {
        log_error("error: register index out of bounds");
        // TODO signals
    }
    if (index == 0) {
        // TODO signals
        log_error("error: setting zero registers");
    }
    RegisterType type = pulse_register_get_type(index);
    switch (type) {
        case REGISTER64:
            registers->regInt[index].val.reg64 = data;
        break;
        case REGISTER32:
            registers->regInt[index].val.reg32 = (uint32_t) data;
        break;
        case REGISTER16:
            registers->regInt[index].val.reg16 = (uint16_t) data;
        break;
        case REGISTER8:
            registers->regInt[index].val.reg8 = (uint8_t) data;
        break;
        // Uses Different method for Float and vector registers
        case REGISTER_FLOAT64:
        break;
        case REGISTER_VECTOR:
          break;
        }
}

int64_t pulse_register_int_get(RegisterFile* registers, int8_t index) {
    if (index < 0 || index > REGISTER_SIZE) {
        // TODO Signals 
    }
    return registers->regInt[index].val.reg64;
}

uint64_t* pulse_register_int_get_adrs(RegisterFile* registers, int8_t index) {
    if (index < 0 || index > REGISTER_SIZE) {
        // TODO Signals 
    }
    return &registers->regInt[index].val.reg64;
}

int64_t pulse_register_get_pc(RegisterFile* registers) {
    return registers->pc;
}

void pulse_register_set_pc(RegisterFile* registers, int64_t data) {
    registers->pc = data;
}

int64_t pulse_register_get_ir(RegisterFile* registers) {
    return registers->ir;
}

void pulse_register_set_ir(RegisterFile* registers, uint64_t data) {
    registers->ir = data;
} 

RegisterType pulse_register_get_type(int idx) {
    if (idx < REG_REGISTER_INT_END)         return REGISTER64;
    else if (idx < REG_REGISTER8_END)       return REGISTER8;
    else if (idx < REG_REGISTER16_END)      return REGISTER16;
    else if (idx < REG_REGISTER32_END)      return REGISTER32;
    else if (idx < VECTOR_REGISTER_END)     return REGISTER_VECTOR;
    else                                    return REGISTER64; // default/fallback/error
}

double pulse_register_double_get(RegisterFile* registers, int index) {
    if (index < 0 || index > REGISTER_SIZE) {
        // TODO Signals 
    }
    return registers->regFloat[index];
}

double* pulse_register_double_get_adrs(RegisterFile* registers, int index) {
    if (index < 0 || index > REGISTER_SIZE) {
        // TODO Signals 
    }
    return &registers->regFloat[index];
}

void pulse_register_double_set(RegisterFile* registers, int index, double val) {
    if (index < 0 || index > REGISTER_SIZE) {
        // TODO Signals 
    }
    registers->regFloat[index] = val;
}

