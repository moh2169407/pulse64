#include "pulse.h"
#include "bus.h"
#include "isa_gen.h"
#include "operand.h"
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
    pulse_core_exe(instance);
    pulse_core_move(core, instance);
    pulse_core_mem_wb(core, instance);
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

    InstructionInstance* instance = pulse_isa_init_instruction_instance(info->inputOperandSize);
    instance->info = info;
    instance->outputIdx = context.RC;

    for (int i = 0; i < info->inputOperandSize; i++) {
        OperandFormat format;
        switch (info->source[i]) {
            case SOURCE_NONE:
                format.type = OPERAND_NONE;
            break;
            case SOURCE_RC_I:
                format.data = pulse_register_int_get_adrs(core->registers, context.RC);
                format.type = OPERAND_REGISTER_I;
            break;
            case SOURCE_RC_F:
                format.data = pulse_register_float_get_adrs(core->registers, context.RC);
                format.type = OPERAND_REGISTER_F;
            break;
            case SOURCE_RB_I:
                format.data = pulse_register_int_get_adrs(core->registers, context.RB);
                format.type = OPERAND_REGISTER_I;
            break;
            case SOURCE_RB_F:
                format.data = pulse_register_float_get_adrs(core->registers, context.RB);
                format.type = OPERAND_REGISTER_F;
              break;
            case SOURCE_RA_I:
                format.data = pulse_register_int_get_adrs(core->registers, context.RA);
                format.type = OPERAND_REGISTER_I;
                break;
            case SOURCE_RA_F:
                format.data = pulse_register_float_get_adrs(core->registers, context.RA);
                format.type = OPERAND_REGISTER_F;
                break;
            case SOURCE_CONSTANT:
                format.data = &context.Const;
                format.type = OPERAND_CONSTANT;
              break;
            }
    instance->opformat[i] = format; 
    }
    return instance;
}

void pulse_core_exe(InstructionInstance* instance) {
    if (instance->info->usesExe) {
        void* source1 = instance->opformat[0].data;
        void* source2 = instance->opformat[1].data;
        instance->info->alu_fn(source1, source2, instance->output);
    }
}

void pulse_core_move(Pulse* core, InstructionInstance* instance) {
    if (instance->info->branch) {
        if (instance->branchTake) {
            pulse_register_set_pc(core->registers, pulse_register_int_get(core->registers, instance->outputIdx));
        }
    }
    if (instance->info->usesMove) {
        void* source1 = instance->opformat[0].data;
        void* source2 = instance->opformat[1].data;
        instance->info->move_fn(source1, source2, instance->output);        
    }
}

void pulse_core_mem_wb(Pulse* core, InstructionInstance* instance) {
    if (instance->info->usesMem) {

    }
    if (instance->info->usesWb) {
        pulse_registers_int_set(core->registers, instance->outputIdx, *(int64_t*) instance->output->data);
    }
    pulse_isa_free_instruction_instance(instance);
}
