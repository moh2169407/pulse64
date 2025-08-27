/** Author: Mohamud Mohamud
 *  Date: Aug 20, 2025
 *  Description: This file emulates the bus found in hardware
 *  It allow for communication between different hardware components,
 *  allowing exactly a single source to pass data
 */

#ifndef BUS_H
#define BUS_H

#include <stdint.h>

/*
* The current component writing to bus
*/
typedef enum {
    BUS_OWNER_NONE,
    BUS_OWNER_CPU,
    BUS_OWNER_RAM,
} BusOwner;

/**
* Bus are defined as long(64 Bits)
* but can use the following method
* to access certain bytes
*/
typedef struct {
    union {
        uint64_t word;
        uint32_t half;
        uint16_t hhalf;
        uint8_t byte[8];
    };
    BusOwner owner; 
} Bus;

// Initializing and Free 

/*
* Creates a bus structure
*/
Bus* pulse_bus_init();

/*
* Free the bus structure
*/
void pulse_bus_free(Bus* bus);

// Writing data

/*
* Write 64 bit of data to bus, only if the bus has no owner
* or that component is already writing data
*/
void pulse_bus_write64(Bus* bus, uint64_t data, BusOwner owner);

/*
* Write 32 bit of data to bus, only if the bus has no owner
* or that component is already writing data
*/
void pulse_bus_write32(Bus* bus, uint32_t data, BusOwner owner);

/*
* Write 16 bit of data to bus, only if the bus has no owner
* or that component is already writing data
*/
void pulse_bus_write16(Bus* bus, uint16_t data, BusOwner owner);

/*
* Write 8 bit of data to bus, only if the bus has no owner
* or that component is already writing data
*/
void pulse_bus_write8(Bus* bus, uint16_t data, BusOwner owner);

/**
* Writes data to one of the 8 bytes inside the long
* sets the bus to zero if the index is greater than 0-7
*/
void pulse_bus_set_byte(Bus* bus, int index, uint8_t byte, BusOwner owner);

// Reading Data
/**
* Return 64 bits of data from bus
*/
uint64_t pulse_bus_read64(Bus* bus);

/**
* Return 32 bits of data from bus
*/
uint32_t pulse_bus_read32(Bus* bus); 

/**
* Return 16 bits of data from bus
*/
uint16_t pulse_bus_read16(Bus* bus);

/**
* Return the last 8 bits of data from bus
*/
uint8_t pulse_bus_read8(Bus* bus);

/**
* Return a byte 0 - 7 based on index
* Returns zero if the index is out bounds
*/
uint8_t pulse_bus_read_byte(Bus* bus, int index);

/**
* Remove the owner of bus, allowing other components to 
* write
*/
void pulse_bus_release_owner(Bus* bus);

/**
* Gets who is the owner of bus
*/
BusOwner pulse_bus_get_owner(Bus* bus);

/**
* Writes a zero, clearing the bus
*/
void pulse_bus_clear(Bus* bus);

#endif
