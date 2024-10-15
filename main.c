#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define MEMORY_SIZE 8
#define REGISTER_NUMBER 4
#define MAX_COMMAND_LENGHT 8

struct CPU{
    uint8_t memory[MEMORY_SIZE];
    uint8_t registers[REGISTER_NUMBER];
    uint8_t regnum;
    uint8_t opcode;
    uint8_t operand;
    uint8_t imm;
    uint8_t PC;
    uint8_t destreg;
};

void reset(struct CPU *cpu){
    for (int i = 0;i < MEMORY_SIZE;i++){
        cpu->memory[i] = 0;
    }
    for(int j = 0;j < REGISTER_NUMBER;j++){
        cpu->registers[j] = 0;
    }
    printf("reset \n");
    cpu->PC = 0;
}

void print(struct CPU *cpu){
    for (int i = 0;i < MEMORY_SIZE;i++){
        printf("%d \n", cpu->memory[i]);
    }
    for(int j = 0;j < REGISTER_NUMBER;j++){
        printf("register:%d \n", cpu->registers[j]);
    }
    printf("Program counter value %d \n", cpu->PC);
}

void execute(struct CPU *cpu){
    switch (cpu->opcode) {
        case 0x00: //LDR
            cpu->registers[cpu->regnum] = cpu->memory[cpu->operand];
            cpu->PC++;
            break;
        case 0x01: //ADD
            cpu->registers[cpu->regnum] += cpu->memory[cpu->operand];
            cpu->PC++;
            break;
        case 0x02: //SUB
            if (cpu->registers[cpu->regnum] > cpu->memory[cpu->operand]){
                cpu->registers[cpu->regnum] -= cpu->memory[cpu->operand];
            }
            else{
                printf("Error: cannot divide register value is smaller than memory operand\n");
            }
            cpu->PC++;
            break;
        case 0x03: //MUL
            cpu->registers[cpu->regnum] *= cpu->memory[cpu->operand];
            cpu->PC++;
            break;
        case 0x04: //DIV
            if (cpu->memory[cpu->operand] == 0){
                printf("Error: division by zero \n");
            }
            else{
                cpu->registers[cpu->regnum] /= cpu->memory[cpu->operand];
            }
            cpu->PC++;
            break;
        case 0x05: //RST
            reset(cpu);
            break;
        case 0x06: //HLT
            printf("halted \n");
            exit(0);
            break;
        case 0x07: //LDM
            cpu->memory[cpu->operand] = cpu->imm;
            printf("Loaded %d into memory[%d]\n", cpu->imm, cpu->operand);
            cpu->PC++;
            break;
        case 0x08: //STM
            cpu->memory[cpu->operand] = cpu->registers[cpu->regnum];
            cpu->PC++;
            break;
        case 0x09: //NOP
            cpu->PC++;
            break;
        case 0x0A: //INC
            cpu->registers[cpu->regnum] += 1;
            cpu->PC++;
            break;
        case 0x0B: //DEC
            cpu->registers[cpu->regnum] -= 1;
            cpu->PC++;
            break;
        case 0x0C: //MOV
            cpu->registers[cpu->destreg] = cpu->registers[cpu->regnum];
            cpu->PC++;
            break;
        default:
            printf("Error: Unknown Instruction Opcode %02x\n", cpu->opcode);
            break;
    }
}

int main(void){
    struct CPU cpu;
    reset(&cpu);
    
    FILE *file;
    file = fopen("asm.b", "rb");
    
    uint8_t cmd[MAX_COMMAND_LENGHT];
    
    if (file == NULL) {
        printf("File not opened");
        return 1;
    }
    
    while(fread(cmd, sizeof(uint8_t), 1, file) == 1){
        cpu.opcode = cmd[0];
        if(cpu.opcode == 0x05 || cpu.opcode == 0x09){
            execute(&cpu);
        }
        else if(cpu.opcode == 0x0A || cpu.opcode == 0x0B){
            fread(&cmd[1], sizeof(uint8_t), 1, file);
            cpu.regnum = cmd[1];
            execute(&cpu);
        }
        else if(cpu.opcode == 0x07){
            fread(&cmd[1], sizeof(uint8_t), 2, file);
            cpu.operand = cmd[1];
            cpu.imm = cmd[2];
            execute(&cpu);
        }
        else if(cpu.opcode == 0x0C){
            fread(&cmd[1], sizeof(uint8_t), 2, file);
            cpu.regnum = cmd[1];
            cpu.destreg = cmd[2];
            execute(&cpu);
        }
        else{
            fread(&cmd[1], sizeof(uint8_t), 2, file);
            cpu.operand = cmd[1];
            cpu.regnum = cmd[2];
            execute(&cpu);
        }
    }
    
    print(&cpu);

    fclose(file);
    
    return 0;
}
