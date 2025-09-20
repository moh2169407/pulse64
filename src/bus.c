#include "bus.h"
#include "svec.h"


Bus* pulse_bus_init() {
    Bus* bus = xmalloc(sizeof(*bus));
    bus->word = 0;
    return bus;
}

void pulse_bus_free(Bus* bus) {
    free(bus);
}

// Writing data

void pulse_bus_write64(Bus* bus, uint64_t data, BusOwner owner) {
    if (bus->owner == BUS_OWNER_NONE || bus->owner == owner) {
        pulse_bus_clear(bus);
        bus->word = data; 
    }
}

void pulse_bus_write32(Bus* bus, uint32_t data, BusOwner owner) {
    if (bus->owner == BUS_OWNER_NONE || bus->owner == owner) {
        pulse_bus_clear(bus);
        bus->half = data;
    }
}

void pulse_bus_write16(Bus* bus, uint16_t data, BusOwner owner) {
    if (bus->owner == BUS_OWNER_NONE || bus->owner == owner) {
        pulse_bus_clear(bus);
        bus->hhalf = data;
    }
}

void pulse_bus_write8(Bus* bus, uint16_t data, BusOwner owner) {
    if (bus->owner == BUS_OWNER_NONE || bus->owner == owner) {
        pulse_bus_clear(bus);
        bus->byte[7] = data;
    }
}

void pulse_bus_set_byte(Bus* bus, int index, uint8_t byte, BusOwner owner) {
    if (bus->owner == BUS_OWNER_NONE || bus->owner == owner) {
        if (index < 0 || index > 7) {
            pulse_bus_clear(bus);
        }
        else {
            bus->byte[index] = byte;
        }
    }
}

// Reading Data

uint64_t pulse_bus_read64(Bus* bus) {
    return bus->word;
}

uint32_t pulse_bus_read32(Bus* bus) {
    return bus->half;
}

uint16_t pulse_bus_read16(Bus* bus) {
    return bus->hhalf;
}

uint8_t pulse_bus_read8(Bus* bus) {
    return bus->byte[7];
}

uint8_t pulse_bus_read_byte(Bus* bus, int index) {
    if (index < 0 || index  < 7) {
        return 0;
    }
    else {
        return bus->byte[index];
    }
}

void pulse_bus_release_owner(Bus* bus) {
    bus->owner = BUS_OWNER_NONE;
}

BusOwner pulse_bus_get_owner(Bus* bus) {
    return bus->owner;
}

void pulse_bus_clear(Bus* bus) {
    bus->word = 0;
}


