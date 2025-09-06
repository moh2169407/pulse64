#ifndef PULSE_H
#define PULSE_H

#include "ram.h"
#include "register.h"
#include "bus.h"
#include "isa_gen.h"

#include <stdint.h>

#define OPCODE_END_BIT 25
#define OPCODE_SIZE 7
#define TYPE_END_BIT 23
#define TYPE_SIZE 2
#define RC_END_BIT 18 
#define RC_SIZE 5
#define RB_END_BIT 13
#define RB_SIZE 5
#define RA_END_BIT 8
#define RA_SIZE 5

struct MemBuses;

typedef struct {
    RegisterFile* registers;    
    MemBuses* membuses;
} Pulse;

typedef struct {
    int8_t opcode;
    int8_t type;
    int8_t RC;
    int8_t RB;
    int8_t RA;
    int16_t Const;
} InstruContext;



Pulse* pulse_core_init(MemBuses* membuses);

void pulse_core_free(Pulse* core);


void pulse_core_run(Pulse* cpu);

void pulse_core_step(Pulse* core, Ram* ram);

// Stages of the processor

void pulse_core_fetch(Pulse* core, Ram* ram);

InstructionInstance* pulse_core_decode(Pulse* core);

void pulse_core_exe(InstructionInstance* instance);

void pulse_core_move(Pulse* core, InstructionInstance* instance);

void pulse_core_mem_wb(Pulse* core, InstructionInstance* instance);
#endif 
