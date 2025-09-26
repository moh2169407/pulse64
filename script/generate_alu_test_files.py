import sys
import yaml

try:
    with open ("../tests/test_alu.yaml", "r") as yamlFile:
        data = yaml.safe_load(yamlFile)
except FileNotFoundError:
    print("ERROR: ALU test yaml file doesn't exisit") 
    sys.exit(1)

with open ("../tests/test_alu_gen.c" , "w") as outFile:
    outFile.write("#include \"alu.h\"\n")
    outFile.write("#include \"log.h\"\n")
    outFile.write("#include <stdbool.h>\n")
    outFile.write("#include <stdint.h>\n")
    outFile.write("\n\n")

    outFile.write("bool isFailing = false;\n")
    outFile.write("\n")

    # Iterate through the tests inside data
    for tests in data:
        name = tests.get("Name") or None
        fn = tests.get("fn") or None
        inputType = tests.get("inType")
        outType = tests.get("outType")
        cases = tests.get("test_cases") or []
        checkOverFlow = tests.get("checkOverFlow") or None
        checkUnderFlow = tests.get("checkUnderFlow") or None
        checkSwap = tests.get("checkSwap");


        outFile.write(f"void {name}() {{\n")
        outFile.write("\t// stores the alu outputs\n")
        outFile.write("    OperandFormat format;\n")
        outFile.write(f"    {outType} x = 0;\n")
        outFile.write("    format.data = &x;\n");

        outFile.write(f"    {inputType} source1;\n")
        outFile.write(f"    {inputType} source2;\n")

        i = 0
        for case in cases:
            outFile.write("\n")
            outFile.write(f"    // test case {i + 1}:\n")
            outFile.write(f"    source1 = {case[0]};\n")
            outFile.write(f"    source2 = {case[1]};\n")

            outFile.write(f"    {fn}(&source1, &source2, &format);\n")

            outFile.write(f"    if (*({outType}*)format.data != {case[2]}) {{\n")
            outFile.write(f"        log_trace(\"{name} test case: {i} failed ❌\");\n")
            outFile.write(f"        isFailing = true;\n")
            outFile.write(f"    }}\n    else{{\n")
            outFile.write(f"        log_trace(\"{name} (test case: {i}) passed ✅\");\n")
            outFile.write("    }\n")

            i += 1

        if checkUnderFlow:
            outFile.write(f"    // test case underflow:\n")
            if inputType == "int64_t":
                outFile.write(f"    source1 = INT_MIN64;\n") 
                outFile.write(f"    source2 = 1;\n") 
        outFile.write("}\n\n\n");

    outFile.write("int main(void) {\n")
    for i in data:
        name = i.get("Name")
        outFile.write(f"    {name}();\n") 

    outFile.write("}\n")
