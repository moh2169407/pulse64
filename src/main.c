#include "log.h"

#include "pangea.h"
#include "pulse.h"


int main(void) {
    Pangea* pangea = pulse_pangea_boot();

    // setting pc 
    pulse_register_set_pc(pangea->cpu->registers, 0);

    // Hard coding first instruction
    // // TODO loader firmware that loads bios 
    //
    // 0000000 -> Opcode : 7
    // 00 -> Size : 2
    // 00010 -> RC : 5
    // 00001 -> RB : 5
    // 00000 -> RA : 5
    // Reserved

    // 0000 0000 0000 1000 0010 0000 0000 0000
    // 0x00 
    // 0x08
    // 0x20
    // 0x00
    // 0x00082000 -> little endian : 0x00028000

    // Little Endian
    pangea->ram->mem[0] = 0x00;
    pangea->ram->mem[1] = 0x20;
    pangea->ram->mem[2] = 0x08;
    pangea->ram->mem[3] = 0x00;

    pulse_core_step(pangea->cpu, pangea->ram);


    pulse_pangea_shut_down(pangea);
}
