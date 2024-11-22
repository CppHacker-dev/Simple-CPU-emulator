# Simple-CPU-emulator

This is a simple cpu emulator meant as a learning project

This repository contains a simple CPU emulator written in C. The emulator mimics a minimalistic CPU architecture, consisting of registers, memory, and a set of basic instructions. The program reads binary-encoded assembly instructions from a file, executes them on the simulated CPU, and prints the state of the registers and memory.
Features

    Memory & Registers:
        8 bytes of memory (MEMORY_SIZE = 8).
        4 general-purpose 8-bit registers (REGISTER_NUMBER = 4).
        Program Counter (PC) to keep track of the current instruction.
    Instruction Set: The emulator supports a variety of operations, including:
    LDR (0x00): Load a value from memory into a register.
    ADD (0x01): Add a memory value to a register.
    SUB (0x02): Subtract a memory value from a register.
    MUL (0x03): Multiply a register by a memory value.
    DIV (0x04): Divide a register by a memory value (error on division by zero).
    RST (0x05): Reset the CPU (clear registers and memory).
    HLT (0x06): Halt the CPU.
    LDM (0x07): Load an immediate value into memory.
    STM (0x08): Store a register value into memory.
    NOP (0x09): No operation.
    INC (0x0A): Increment a register.
    DEC (0x0B): Decrement a register.
    MOV (0x0C): Move the value of one register to another.
    OR  (0x10): Perform a bitwise OR between a register and a memory value.
    XOR (0x11): Perform a bitwise XOR between a register and a memory value.
    NOT (0x12): Perform a bitwise NOT on a register.


File Structure

    main.c: The main code file containing the CPU struct, the instruction execution logic, and file handling code.
    asm.b: A sample binary file (assembly) containing instructions that the emulator reads and executes.

How It Works

    The CPU is initialized with all memory and registers set to 0.
    Instructions are read from a binary file (asm.b), one by one.
    Based on the opcode of each instruction, the corresponding operation is performed on the CPU.
    The emulator continues until a halt (HLT) instruction is encountered.
    After the program execution, the final state of the CPU registers and memory is printed.

Instruction Format

Each instruction consists of one or more bytes, depending on the opcode:

    Single-byte instructions (like NOP, RST, HLT) only require the opcode.
    Two-byte instructions (like INC, DEC) include an opcode followed by the register number.
    Three-byte instructions (like LDM, MOV) include an opcode followed by the operand or register values.

Example Instruction Encoding:

    LDM 0x02, 0x10 (Load immediate value 0x10 into memory address 0x02) is encoded as:
        Opcode: 0x07
        Operand: 0x02
        Immediate Value: 0x10
        Binary Representation: 07 02 10

How to Run
Prerequisites

A C compiler (GCC, Clang, etc.).
A binary file (asm.b) containing CPU instructions in the correct format.

    git clone https://github.com/CppHacker-dev/simple-cpu-emulator.git
    cd simple-cpu-emulator

Compile the program using your C compiler:

bash

    gcc main.c -o cpu_emulator

Running the Emulator

Make sure you have a binary instruction file (asm.b) in the same directory.
Run the emulator:

bash

    ./cpu_emulator

Example asm.b File

Here is a simple example of the instruction set in a binary file (asm.b):

    07 02 10  # LDM: Load 0x10 into memory address 0x02
    00 01 02  # LDR: Load memory[0x02] into register 1
    01 01 02  # ADD: Add memory[0x02] to register 1
    0A 01     # INC: Increment register 1
    06        # HLT: Halt the program

Output

Upon running the program, it prints the state of memory and registers after executing all instructions, as well as the program counter value.

Example output:

Memory[0] = 0 
Memory[1] = 0 
Memory[2] = 16
Memory[3] = 0 
Memory[4] = 0 
Memory[5] = 0 
Memory[6] = 0 
Memory[7] = 0 
Register[0] = 0 
Register[1] = 18 
Register[2] = 0 
Register[3] = 0 
Program counter value: 5

Contributing

Feel free to fork this project, report issues, and submit pull requests. Contributions are welcome!
