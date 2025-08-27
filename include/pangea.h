#ifndef PANGEA_H
#define PANGEA_H

#include "pulse.h"
#include "ram.h"

struct MemBuses{
    Bus* read;
    Bus* write;
    Bus* data;
    Bus* address;
};

/**
* The main struct that holds the cpu,
* ram, buses and other hardware componenet
*/
typedef struct {
    Pulse* cpu;
    Ram* ram;
    MemBuses* memBuses;
} Pangea;

/*
* Initializes the Pangea struct,
* the cpu, registers, ram
* and i/o ports
*/
Pangea* pulse_pangea_boot();

/**
* Frees all hardware components 
*/
void pulse_pangea_shut_down(Pangea* pangea);

/**
* Defines the main loop for the processor execution
*/
void pulse_pangea_main_loop(Pangea* pangea);

MemBuses* pulse_pangea_init_mem_buses();

void pulse_pangea_free_mem_buses(MemBuses* memBuses);

void pulse_pangea_main_loop(Pangea* pangea);

#endif
