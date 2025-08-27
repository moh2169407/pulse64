#include "pulse.h"
#include "bus.h"
#include "isa_gen.h"
#include "pangea.h"

#include "../../svec/svec.h"
#include "ram.h"
#include "register.h"
#include <assert.h>
#include <stdint.h>

#define BIT_MASK(N) ((1U << (N)) - 1)

// == Private Functions ========================================================

static inline uint32_t _shift_and_mask(uint32_t ir, uint8_t shift, uint8_t mask) {
    return (ir >> shift) & BIT_MASK(mask);
}

// == Public Functions ========================================================

Pulse* pulse_core_init(MemBuses* membuses) {
    assert(membuses);
    Pulse* core = xmalloc(sizeof(*core));
    core->membuses = membuses;
    core->registers = pulse_registers_init();
    return core;
}

void pulse_core_free(Pulse* core) {
    pulse_registers_free(core->registers);
    free(core);
}

void pulse_core_run(Pulse* cpu) {

}

void pulse_core_step(Pulse* core, Ram* ram) {
    pulse_core_fetch(core, ram);
    InstructionInstance* instance = pulse_core_decode(core);
    pulse_core_exe(core, instance);
    // pulse_core_move(core, info);
    // pulse_core_mem_wb(core, info);
}

void pulse_core_fetch(Pulse* core, Ram* ram) {
    assert(core->membuses);
    pulse_bus_write64(core->membuses->address, core->registers->pc, BUS_OWNER_CPU);
    pulse_bus_write8(core->membuses->read, READ, BUS_OWNER_CPU);
    pulse_ram_tick(ram);

    pulse_bus_release_owner(core->membuses->read);
    pulse_bus_release_owner(core->membuses->write);
    
   pulse_register_set_ir(core->registers, pulse_bus_read64(core->membuses->data));

}

InstructionInstance* pulse_core_decode(Pulse* core) {
    InstruContext context;
    context.opcode = _shift_and_mask(core->registers->ir, OPCODE_END_BIT, OPCODE_SIZE);
    context.type = _shift_and_mask(core->registers->ir, TYPE_END_BIT, TYPE_SIZE);
    context.RC = _shift_and_mask(core->registers->ir, RC_END_BIT, RC_SIZE);
    context.RB =  _shift_and_mask(core->registers->ir, RB_END_BIT, RB_SIZE);
    context.RA =  _shift_and_mask(core->registers->ir, RA_END_BIT, RA_SIZE);

   const InstructionInfo* info = pulse_isa_get_instruction_info(context.opcode, context.type); 

    InstructionInstance* instance = xmalloc(sizeof(*instance));
    instance->info = info;

    for (int i = 0; i < FORMAT_SIZE; i++) {
        switch (info->format[i]) {
        case OPERAND_NONE:
            break;
        case OPERAND_REGISTER_I:
                if (i == 0) {
                    instance->inputI[i] = pulse_register_get(core->registers, context.RB);
                }
                else if (i == 1) {
                    instance->inputI[i] = pulse_register_get(core->registers, context.RA);
                }
            break;
        case OPERAND_REGISTER_F:
                break;
        case OPERAND_CONSTANT:
            break;
        case OPERAND_MEM:
                break;
          break;
        }
    }


    return instance;
}

void pulse_core_exe(Pulse* core, InstructionInstance* instance) {

}

void pulse_core_move(Pulse* core, const InstructionInfo* info) {

}

void pulse_core_mem_wb(Pulse* core, const InstructionInfo* info) {

}












