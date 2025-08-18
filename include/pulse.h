#ifndef PULSE_H
#define PULSE_H

#include "ram.h"
#include "register.h"
#include "bus.h"


struct MemBuses;

typedef struct {
    Registers* registers;    
    MemBuses* membuses;
} Pulse;

typedef struct {
    int8_t instru;
    int8_t type;
    int64_t source1;
    int64_t source2;
    int64_t out;
} InstruContext;

Pulse* pulse_core_init();

void pulse_core_free();

int32_t pulse_core_fetch(Pulse* core);

InstruContext pulse_core_decode(Pulse* core);

void pulse_core_exe(InstruContext context);

void pulse_core_move(InstruContext context);

void pulse_core_mem_wb(InstruContext context);
#endif 
