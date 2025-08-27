#ifndef RAM_H
#define RAM_H

#include <stdint.h>
#include <stdbool.h>

typedef struct MemBuses MemBuses;

#define MEM_SIZE 1000
#define ERROR 1
#define CLEAN 0

#define READ 1
#define WRITE 1

typedef struct {
    int8_t* mem;   /*Main memory with MEM_SIZE*/
    MemBuses* buses; 
} Ram;

Ram* pulse_ram_init(MemBuses* memBuses);

void pulse_ram_free(Ram* ram);

int pulse_ram_tick(Ram* ram);

#endif
