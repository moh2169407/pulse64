<h1> Pulse64 </h1>

### Technical Reference Manual 
> Manual is a living document, and will change as the processor changes

---

### Table of Contents
* [Chapter 1: About the processor](#chapter-1)
* [Chapter 2: Program Model](#chapter-2)
* [Chapter 3: Instructions Format](#instruction-format)
* [Chapter 4: Instruction Encoding](#instruction-encoding)
    * [R-Type](#r-type)
    * [I-Type](#i-type)
* [Chapter 4: ISA](#isa)


## Chapter 1
##### About the processor: 
* Pulse64 is a toy custom virtual processor takes ideas from arms and x86 based processor and adds some unique quirks. The purpose of processor is to help me understand low level
systems, and what better way than replicating hardware and software from the ground up. The vision for this project keep it extensible, so that I can add new features as I learn

##### Includes:
1. [Custom ISA](ISA)
2. Stack Pointer
3. Bus System. The only way the processor communicates with other hardware  
4. Big Endian
5. Exceptions Model
6. Eight Stage Pipeline

##### Note:
This project aims to emulate the processor at a low level, meaning there is a propagation delay to replicate memory, buses to communicates and realistic clock cycles, 
this comes at the cost of performance, while this isn't a problem right now, I might add a mode later that focuses on replicating the functionality without necessarily simulating every aspect 


## Chapter 2
##### Program Model:
* Register:
    * The processor has the following 64 registers
        - 32 Integer Register
            - $R0 - $R31 can be used to access the register, but a naming convention is used to provide context
            - $R0 is the zero register and value cant not be set
            - AR1, AR2, AR3 -> $R1, $R2, $R3 = Registers used for arguments
            - OP1, OP2, OP3 -> $R4, $R5, $R6 = Registers used for outputs 
            - SMD1, SMD2, SMD3 -> $R7, $R8, $R9 = Used for vector arithmetic, each stores 5 words (320 Bits)
            - SMD1.A - SMD1.E to access each int
            - RG32.A, RG32.B, RG32.C -> $R10, $R11, $R12 = 32 bit register
            - RG16.A, RG16.B, RG16.C -> $R13, $R14, $R15 = 32 bit register
            - RG8.A, RG8.B, RG8.C -> $R16, $R17, $R18 = 32 bit register
        - 32 Floating Point Register 
            - $F0 - $F31 can be used to access the register, but a naming convention is used to provide context
            - $F0 is the zero register and value cant not be set
            - FAR1, FAR2, FAR3 -> $F1, $F2, $F3 = Registers used for arguments
            - FOP1, FOP2, FOP3 -> $F4, $F5, $F6 = Registers used for outputs 
        - Special Register
            - PC -> Holds the instruction address (64 Bit)
            - IR -> Holds the current instruction (32 Bit)
            - SP -> Holds the stack pointer (64 Bit)
            - ES -> Holds the exception status (16 Bit)
* Data Types: 
    - 64-bit word
    - 32-bit half
    - 16-bit hhalf
    - 8- bit Byte

##### Instruction Format:
- R Type -> Arithmetic operations on all register
- I Type -> Arithmetic operations on register and immediate constant 
- M Type -> Moving data between register, int reg -> floating and vis versa
and also moving constant to registers
- Sys Type -> For os operations 


##### Instruction Encoding:
#### R-Type

| Opcode | Size | RC  | RB | RA | Reserved
| ---- | ---- | --- | --- | --- | ---
| 7 Bits | 2 Bits | 5 Bits | 5 Bits | 5 Bits| 8 bits

* Opcode:
The instruction the processor is going perform
* Size:
Selects the type of instruction variant
* Register: RC, RB, and RA are the regular register whose values are action to perform,
values are set to RC

#### I-Type
| Opcode | Size | RC  | RB | Constant
| ---- | ---- | --- | --- | --- |
| 7 Bits | 2 Bits | 5 Bits | 5 Bits | 13 Bits

* Opcode:
The instruction the processor is going perform
* Size:
Selects the type of instruction variant
* Register: 
RC, and RB are the regular register whose values are action to perform,
values are set to RC
* Constant: range 0 - 8192

#### M-Type
| Opcode |  RC  | RB/Constant
| ---- | --- | --- |
| 7 Bits | 5 Bits | 5 Bits  or 18 Bits

#### S-Type
| Opcode |  RC  
| ---- | --- | 
| 7 Bits | 5 Bits 


#### J-Type
| Opcode |  RC  
| ---- | --- | 
| 7 Bits | 5 Bits 


## Chapter 3

### ISA

R-Type

##### ADD : 0

|Size| Assembly Example | C Equivalent |
| --- | --- | ---|
|0| ADD RC, RB, RA | RC = RB + RA |
|1| ADDU RC, RB, RA | (unsigned) RC = RB + RA |
|2| ADDF FC, FB, FA | FC = FB + FA |
|3| ADDV SMD, SMD, SMD | C = {a} + {b}

##### SUB : 1

|Size| Assembly Example | C Equivalent |
| --- | --- | ---|
|0| SUB RC, RB, RA | RC = RB - RA |
|1| SUBU RC, RB, RA | (unsigned) RC = RB - RA |
|2| SUBF FC, FB, FA | FC = FB - FA |
|3| SUBV SMD, SMD, SMD | C = {a} - {b}


##### MUL : 2

|Size| Assembly Example | C Equivalent |
| --- | --- | ---|
|0| MUL RC, RB, RA | RC = RB * RA |
|1| MULU RC, RB, RA | (unsigned) RC = RB * RA |
|2| MULF FC, FB, FA | FC = FB * FA |
|3| MULV SMD, SMD, SMD | C = {a} * {b}


##### DIV : 3

|Size| Assembly Example | C Equivalent |
| --- | --- | ---|
|0| DIV RC, RB, RA | RC = RB / RA |
|1| DIVU RC, RB, RA | (unsigned) RC = RB / RA |
|2| DIVF FC, FB, FA | FC = FB / FA |
|3| DIVV SMD, SMD, SMD | C = {a} / {b}


##### MOD : 4

|Size| Assembly Example | C Equivalent |
| --- | --- | ---|
|0| MOD RC, RB, RA | RC = RB % RA |
|1| MODU RC, RB, RA | (unsigned) RC = RB % RA |
|2| MODF FC, FB, FA | FC = FB % FA |
|3| MODV SMD, SMD, SMD | C = {a} % {b}


##### AND(Bitwise) : 5

|Size| Assembly Example | C Equivalent |
| --- | --- | ---|
|0| AND RC, RB, RA | RC = RB & RA |
|1| OR RC, RB, RA |  RC = RB | RA |
|2| XOR RC, RB, RA | RC = RB ^ RA |
|3| NAND RC, RB, RA | RC = ~(RB & RA) |


##### SHR(Bitwise) : 6

|Size| Assembly Example | C Equivalent |
| --- | --- | ---|
|0| SHR RC, RB, RA | SHR = RB >> RA |
|1| SHL RC, RB, RA |  RC = RB << RA |
|2| SHLL RC, RB, RA | RC = (unsigned) RB << RA |
|3| ROR RC, RB, RA | RC = (RB >> RA) | (RB << (N - RA))|


##### B : 7

|Size| Assembly Example | C Equivalent |
| --- | --- | ---|
|0| BEQ RC, RB, RA| PC = if (RB == RA) |
|1| BNE RC, RB, RA|  PC = if (RB != RA) |
|2| BGE RC, RB, RA| PC = if RB > RA|
|3| BLE RC, RB, RA| PC = if (RB < RA) |


I-Type:

##### ADDI : 8

|Size| Assembly Example | C Equivalent |
| --- | --- | ---|
|0| ADDI RC, RB, Constant | RC = RB + Constant |
|1| ADDIU RC, RB, Constant | (unsigned) RC = RB + Constant |
|2| ADDIF FC, FB, Constant | FC = FB + Constant |
|3| ADDIV SMD, SMD, Constant | C = {a} + #constant


##### SUBI : 9

|Size| Assembly Example | C Equivalent |
| --- | --- | ---|
|0| SUBI RC, RB, Constant | RC = RB - Constant |
|1| SUBIU RC, RB, Constant | (unsigned) RC = RB - Constant |
|2| SUBIF FC, FB, Constant | FC = FB - Constant |
|3| SUBIV SMD, SMD, Constant | C = {a} - #constant


##### MULI : 10

|Size| Assembly Example | C Equivalent | 
| --- | --- | ---|
|0| MULI RC, RB, Constant | RC = RB * Constant |
|1| MULIU RC, RB, Constant | (unsigned) RC = RB * Constant |
|2| MULIF FC, FB, Constant | FC = FB * Constant |
|3| MULIV SMD, SMD, Constant | C = {a} * #constant


##### DIVI : 11

|Size| Assembly Example | C Equivalent |
| --- | --- | ---|
|0| DIVI RC, RB, Constant | RC = RB / Constant |
|1| DIVIU RC, RB, Constant | (unsigned) RC = RB / Constant |
|2| DIVIF FC, FB, Constant | FC = FB / Constant |
|3| DIVIV SMD, SMD, Constant | C = {a} / #constant


##### MODI : 12

|Size| Assembly Example | C Equivalent |
| --- | --- | ---|
|0| MODI RC, RB, Constant | RC = RB % Constant |
|1| MODIU RC, RB, Constant | (unsigned) RC = RB % Constant |
|2| MODIF FC, FB, Constant | FC = FB % Constant |
|3| MODIV SMD, SMD, Constant | C = {a} % #constant


##### ANDI(Bitwise) : 13 

|Size| Assembly Example | C Equivalent |
| --- | --- | ---|
|0| ANDI RC, RB, Constant | RC = RB & Constant|
|1| ORI RC, RB, Constant |  RC = RB | Constant|
|2| XORI RC, RB, Constant | RC = RB ^ Constant|
|3| NANDI RC, RB, Constant | RC = ~(RB & Constant) |


##### B : 14 

|Size| Assembly Example | C Equivalent |
| --- | --- | ---|
|0| BEQI RC, RB, Constant | PC = if (RB ==  Constant) |
|1| BNEI RC, RB, Constant |  PC = if (RB != Constant) |
|2| BGEI RC, RB, Constant | PC = if RB > Constant|
|3| BLEI RC, RB, Constant | PC = if (RB < Constant) |


 Memory Instructions

##### LW : 15 

|Size| Assembly Example | C Equivalent |
| --- | --- | ---|
|0| LW RC, RB, RA | RC = MEM[RB + Constant]|
|1| LH RC, RB, RA |  RG32 = MEM[RB + Constant]|
|2| LHH RC, RB, RA |  RG16 = MEM[RB + Constant]|
|3| LB RC, RB, RA | RG8 = MEM[RB + Constant]|


##### SW : 16

|Size| Assembly Example | C Equivalent |
| --- | --- | ---|
|0| SW RC, RB, RA | RC = MEM[RB + Constant]|
|1| SH RC, RB, RA |  RG32 = MEM[RB + Constant]|
|2| SHH RC, RB, RA |  RG16 = MEM[RB + Constant]|
|3| SB RC, RB, RA | RG8 = MEM[RB + Constant]|

 M-Type

##### SWAP : 17

| Assembly Example | C Equivalent |
| --- | ---|
SWAP RC, RB | RC = RB


##### FTOR : 18

| Assembly Example | C Equivalent |
| --- | ---|
 FTOR RC, FB | RC = (int)FB


##### RTOF : 19

| Assembly Example | C Equivalent |
| --- | ---|
 RTOF FC, RB | FC = (double)RB


##### NOT : 20 ~~ Apart of the Move type due to number the input NOT takes ~~

| Assembly Example | C Equivalent |
| --- | ---|
 NOT RC, RB | RC = ~RB


##### NOTF : 21 ~~ Apart of the Move type due to number the input NOT takes ~~

| Assembly Example | C Equivalent |
| --- | ---|
 NOT FC, FB | FC = ~FB


##### CAST : 22

| Assembly Example | C Equivalent |
| --- | ---|
CAST R(Size), R(SIZE) | RC = (Size)RB


##### MOV : 23

| Assembly Example | C Equivalent |
| --- | ---|
MOV R(Size), R(SIZE) | RC = (Size)RB


##### LI : 24

| Assembly Example | C Equivalent |
| --- | ---|
LI R(Size), Constant | RC = Constant

Stack Instructions

##### PUSH : 25

| Assembly Example | C Equivalent |
| --- | ---|
PUSH RC | SP = $RC


##### PULL : 26

| Assembly Example | C Equivalent |
| --- | ---|
PULL RC | RC = SP


##### CALL : 27

| Assembly Example | C Equivalent |
| --- | ---|
CALL RC | RC = PC


##### RET : 28

| Assembly Example | C Equivalent |
| --- | ---|
RET RC |  PC = Ret
 




