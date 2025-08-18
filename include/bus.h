#ifndef BUS_H
#define BUS_H

#include <stdint.h>

typedef enum {
    BUS_OWNER_NONE,
    BUS_OWNER_CPU,
    BUS_OWNER_RAM,
} BusOwner;

typedef enum {
    BUS_SIZE_WORD,
    BUS_SIZE_HALF,
    BUS_SIZE_HHALF
} BusSize;

typedef struct {
    union {
        long word;
        int half;
        int16_t hhalf;
        char byte;
    };
    BusOwner owner; 
    BusSize size; 
} Bus;

typedef struct {
    Bus* read;
    Bus* write;
    Bus* address;
    Bus* data;
} MemBuses;

Bus pulse_bus_init(BusSize size);

void pulse_bus_free(Bus* bus);

void pulse_bus_write(Bus* bus, void* data);

void* pulse_bus_read_word(Bus* bus);

void pulse_bus_release_owner(Bus* bus);

#endif
