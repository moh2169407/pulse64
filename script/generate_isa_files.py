import yaml

class Instruction:
    def __init__(self, name, opcode):
        self.name = name
        self.opcode = opcode

def object_constructor(loader, node):
    value, opcode = loader.construct_scalar(node)
    return Instruction(value, opcode)

# with open("../isa.yaml", "r") as file:
# data =yaml.load(file, Loader=yaml.FullLoader)
# print(data)
# print(type(data))


string = '''
!!python/object:__main__.Instruction
Instruction: 
    - Name: "ADD"
      Opcode: 0
'''

data = yaml.load(string, Loader=yaml.FullLoader)
print(data)
print(type(data))





