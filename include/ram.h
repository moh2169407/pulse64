#ifndef RAM_H
#define RAM_H

#include "bus.h"
#include <stdint.h>
#include <stdbool.h>

struct MemBuses;

#define MEM_SIZE 1000
#define ERROR 1
#define CLEAN 0

typedef struct {
    int8_t** mem;   /*Main memory with MEM_SIZE*/
    MemBuses* buses; 
} Ram;

Ram* pulse_ram_init(MemBuses* memBuses);

void pulse_ram_free(Ram* ram);

int pulse_ram_exe(Ram* ram);

#endif
