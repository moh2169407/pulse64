import yaml
import sys

data = {}

try:
    with open ("../isa.yaml", "r") as yamlFile:
        data = yaml.safe_load(yamlFile)  
except FileNotFoundError:
    print("ERROR: isa file doesn't exisit")
    sys.exit(1)

with open ("../src/isa_gen.c", "w") as outFile:
    outFile.write("#include \"isa_gen.h\" \n")
    outFile.write("#include \"../../svec/svec.h\" \n")
    outFile.write("\n")

    for i in range(0, len(data)):
        outFile.write("static const InstructionInfo ")
        instructionName = data[i]["Name"] + "_Instruction"
        outFile.write(instructionName + " = { \n")
        
        opcode = data[i]["Opcode"]
        size = data[i]["Size"] or 0
        usesSize = data[i]["UsesSize"] or 0
        inputOperandSize = data[i]["InputOperandSize"]
        aluFN = data[i]["ALU_FN"] or "NULL"
        moveFn = data[i].get("MOVE_FN") or "NULL"
        usesMove = str(data[i].get("UsesMove")).lower() or "false"
        usesExe = str(data[i]["UsesExe"]).lower() or "false"
        usesSize = str(data[i]["UsesSize"]).lower() or "false"
        branch = str(data[i]["Branch"]).lower() or "false"
        usesWb = str(data[i]["UsesWb"]).lower() or "false"

        source = None
        if data[i]["Source"] != "NULL":
            source = "{"
            for e in range(0, len(data[i]["Source"])):
                source += data[i]["Source"][e]
                if (e + 1) != len(data[i]["Source"]):
                    source += ", "
            source += "},\n"
        else:
            source = "NULL"




        outFile.write(f"\t.opcode = {opcode},\n")
        outFile.write(f"\t.size = {size},\n")
        outFile.write(f"\t.inputOperandSize = {inputOperandSize},\n")
        outFile.write(f"\t.usesSize = {usesSize},\n")
        outFile.write(f"\t.alu_fn = {aluFN},\n")
        outFile.write(f"\t.move_fn = {moveFn},\n")
        outFile.write(f"\t.usesMove = {usesMove},\n")
        outFile.write(f"\t.usesExe = {usesExe},\n")
        outFile.write(f"\t.branch = {branch},\n")
        outFile.write(f"\t.usesWb = {usesWb},\n")
        outFile.write(f"\t.source = {source}")

        outFile.write("};\n")
        outFile.write('\n')

    outFile.write("const InstructionInfo* instructionTable[INSTRUCTION_LENGTH][VARIANT_LENGTH] =  {\n")
    for i in range(0, len(data)):
        instructionName = data[i]["Name"] + "_Instruction"
        size = data[i]["Size"] or 0
        opcode = data[i]["Opcode"] or 0
        outFile.write(f"\t[{opcode}][{size}] = &{instructionName},\n")
    outFile.write("};")

    outFile.write("""

const InstructionInfo* pulse_isa_get_instruction_info(uint8_t opcode, uint8_t size) {
   const InstructionInfo* info = instructionTable[opcode][0];
    if (!info) {
        return NULL;
    }
    if (info->usesSize) {
        const InstructionInfo* userInfo =  instructionTable[opcode][size];
        return userInfo ? userInfo : NULL;
    }
    return info;
}
    """)


    outFile.write("""
InstructionInstance* pulse_isa_init_instruction_instance(int size) {
    InstructionInstance* instance = xmalloc(sizeof(*instance));
    instance->opformat  = xmalloc(sizeof(*instance->opformat) * size);

    instance->output = xmalloc(sizeof(*instance->output));
    instance->output->data = xmalloc(sizeof(uint64_t));
    return instance;
}
    """)

    outFile.write("""
void pulse_isa_free_instruction_instance(InstructionInstance* instance) {
    free(instance->opformat);
    free(instance->output->data);
    free(instance->output);
    free(instance);
}
    """)


    # for i in range(0, len(data)):
    #     func = data[i].get("ALU_FN")
    #     print(f'void {func}(void* source1, void* source2, OperandType* out);')
