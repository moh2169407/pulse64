#ifndef PANGEA_H
#define PANGEA_H

#include "pulse.h"
#include "ram.h"

/**
* The main struct that holds the cpu,
* ram, buses and other hardware componenet
*/
typedef struct {
    Pulse* cpu;
    Ram* ram;
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
int pulse_pangea_main_loop(Pangea* pangea);

/*
* Moves(Steps) the processor to next stage of execution
*/
int pulse_pangea_step(Pangea* pangea);


#endif
