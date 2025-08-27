#include "pangea.h"
#include "bus.h"
#include "pulse.h"
#include "ram.h"

#include "../../svec/svec.h"


Pangea* pulse_pangea_boot() {
    Pangea* pangea = xmalloc(sizeof(*pangea));
    MemBuses* memBuses = pulse_pangea_init_mem_buses();
    pangea->ram = pulse_ram_init(memBuses);
    pangea->cpu = pulse_core_init(memBuses);
    pangea->memBuses = memBuses;
    return pangea;  
}

void pulse_pangea_shut_down(Pangea* pangea) {
    pulse_pangea_free_mem_buses(pangea->memBuses);
    pulse_core_free(pangea->cpu);
    pulse_ram_free(pangea->ram);
    free(pangea);
}

void  pulse_pangea_main_loop(Pangea* pangea) {
    pulse_core_run(pangea->cpu);
}

MemBuses* pulse_pangea_init_mem_buses() {
    MemBuses* memBuses = xmalloc(sizeof(*memBuses));
    memBuses->address = pulse_bus_init();
    memBuses->data = pulse_bus_init();
    memBuses->read = pulse_bus_init();
    memBuses->write = pulse_bus_init();
    return memBuses;
}

void pulse_pangea_free_mem_buses(MemBuses* memBuses) {
    pulse_bus_free(memBuses->address);
    pulse_bus_free(memBuses->data);
    pulse_bus_free(memBuses->read);
    pulse_bus_free(memBuses->write);
    free(memBuses);
}
