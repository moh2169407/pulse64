#include "ram.h"
#include "../../svec/svec.h"

#include <assert.h>

Ram* pulse_ram_init(MemBuses* memBuses) {
    assert(memBuses);
    Ram* ram = xmalloc(sizeof(*ram));
    ram->mem = xmalloc(sizeof(int8_t) * MEM_SIZE);
    ram->buses = memBuses;
    return ram;
}

void pulse_ram_free(Ram* ram) {
    free(ram->buses);
    free(ram);
}

int pulse_ram_exe(Ram* ram) {

}
