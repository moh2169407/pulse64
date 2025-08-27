#include "ram.h"
#include "../../svec/svec.h"

#include <assert.h>
#include "pangea.h"
#include "bus.h"

Ram* pulse_ram_init(MemBuses* memBuses) {
    assert(memBuses);
    Ram* ram = xmalloc(sizeof(*ram));
    ram->mem = calloc(MEM_SIZE, sizeof(int8_t));
    ram->buses = memBuses;
    return ram;
}

void pulse_ram_free(Ram* ram) {
    free(ram->mem);
    free(ram);
}


int pulse_ram_tick(Ram* ram) {
    uint8_t readBus = pulse_bus_read8(ram->buses->read);
    uint8_t writeBus = pulse_bus_read8(ram->buses->write);
    uint32_t address = pulse_bus_read64(ram->buses->address);

    if (readBus ^ writeBus){
        if (readBus) {
            for (int i = 0; i < 4; i++ ) {
                pulse_bus_set_byte(ram->buses->data, i, ram->mem[address + i], BUS_OWNER_RAM);
            }
        }
        else if (writeBus){
            for (int i = 0; i < 4; i++) {
                ram->mem[address + i] = pulse_bus_read_byte(ram->buses->data, i);
            }
        }
    }
    return CLEAN;
}


