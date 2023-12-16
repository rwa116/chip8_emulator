#include "chip8.hpp"

Chip8::Chip8() {
    memory = Memory();
    cpu = CPU();
    display = Display();
    opcode = 0;
}

void Chip8::LoadProgram(uint8_t* buffer, int size) {
    memory.LoadProgram(buffer, size);
}

void Chip8::Tick() {
    opcode = memory.FetchOpcode(cpu.pc);

    // Decode opcode
    std::cout << "Opcode: " << opcode << std::endl;
    switch(opcode & 0xF000) {
        case 0x0000:
            switch(opcode & 0x000F) {
                case 0x0000: // 0x00E0: Clears the screen
                    display.Clear();
                    cpu.pc += 2;
                    break;
                case 0x000E: // 0x00EE: Returns from subroutine
                    cpu.pc = cpu.stack[cpu.sp];
                    cpu.sp--;
                    cpu.pc += 2;
                    break;
                default:
                    std::cout << "Unknown opcode [0x0000]: 0x" << opcode << std::endl;
            }
            break;
        case 0x1000: // 0x1NNN: Jumps to address NNN
            cpu.pc = opcode & 0x0FFF;
            break;
        case 0x2000: // 0x2NNN: Calls subroutine at NNN
            cpu.sp++;
            cpu.stack[cpu.sp] = cpu.pc;
            cpu.pc = opcode & 0x0FFF;
            break;
        case 0x3000: // 0x3XNN: Skips the next instruction if VX equals NN
            if (cpu.registers[(opcode & 0x0F00) >> 8] == (opcode & 0x00FF)) {
                cpu.pc += 4;
            } else {
                cpu.pc += 2;
            }
            break;
        case 0x4000: // 0x4XNN: Skips the next instruction if VX doesn't equal NN
            if (cpu.registers[(opcode & 0x0F00) >> 8] != (opcode & 0x00FF)) {
                cpu.pc += 4;
            } else {
                cpu.pc += 2;
            }
            break;
        case 0x5000: // 0x5XY0: Skips the next instruction if VX equals VY
            if (cpu.registers[(opcode & 0x0F00) >> 8] == cpu.registers[(opcode & 0x00F0) >> 4]) {
                cpu.pc += 4;
            } else {
                cpu.pc += 2;
            }
            break;
        case 0x6000: // 0x6XNN: Set VX equal to NN
            cpu.registers[(opcode & 0x0F00) >> 8] = opcode & 0x00FF;
            cpu.pc += 2;
            break;
        case 0x7000: // 0x7XNN: Set VX equal to VX plus NN
            cpu.registers[(opcode & 0x0F00) >> 8] += opcode & 0x00FF;
            cpu.pc += 2;
            break;
        case 0x8000:
            switch(opcode & 0x000F) {
                case 0x0000: // 0x8XY0: Set VX equal to VY
                    cpu.registers[(opcode & 0x0F00) >> 8] = cpu.registers[(opcode & 0x00F0) >> 4]; 
                    break;
                case 0x0001: // 0x8XY1: Set VX equal to VX OR VY
                    cpu.registers[(opcode & 0x0F00) >> 8] |= cpu.registers[(opcode & 0x00F0) >> 4]; 
                    break;
                case 0x0002: // 0x8XY2: Set VX equal to VX AND VY
                    cpu.registers[(opcode & 0x0F00) >> 8] &= cpu.registers[(opcode & 0x00F0) >> 4]; 
                    break;
                case 0x0003: // 0x8XY3: Set VX equal to VX XOR VY
                    cpu.registers[(opcode & 0x0F00) >> 8] ^= cpu.registers[(opcode & 0x00F0) >> 4]; 
                    break;
                case 0x0004: // 0x8XY4: Set VX equal to VX plus VY, and set VF to carry
                    if (cpu.registers[(opcode & 0x0F00) >> 8] + cpu.registers[(opcode & 0x00F0) >> 4] > 255) {
                        cpu.registers[0xF] = 1;
                    } else {
                        cpu.registers[0xF] = 0;
                    }
                    cpu.registers[(opcode & 0x0F00) >> 8] += cpu.registers[(opcode & 0x00F0) >> 4];
                    break;
                case 0x0005: // 0x8XY4: Set VX equal to VX minux VY, and set VF to NOT borrow
                    if (cpu.registers[(opcode & 0x0F00) >> 8] > cpu.registers[(opcode & 0x00F0) >> 4] ) {
                        cpu.registers[0xF] = 1;
                    } else {
                        cpu.registers[0xF] = 0;
                    }
                    cpu.registers[(opcode & 0x0F00) >> 8] -= cpu.registers[(opcode & 0x00F0) >> 4];
                    break;
                case 0x0006: //0x8XY5: Set VX equal to VX divided by 2, set VF to LSB of VX
                    cpu.registers[0xF] = cpu.registers[(opcode & 0x0F00) >> 8] & 0b1;
                    cpu.registers[(opcode & 0x0F00) >> 8] /= 2;
                    break;
                case 0x0007: //0x8XY6: Set VX equal to VY minus VX, and set VF to NOT borrow
                    if (cpu.registers[(opcode & 0x00F0) >> 4] > cpu.registers[(opcode & 0x0F00) >> 8] ) {
                        cpu.registers[0xF] = 1;
                    } else {
                        cpu.registers[0xF] = 0;
                    }
                    cpu.registers[(opcode & 0x0F00) >> 8] = cpu.registers[(opcode & 0x00F0) >> 4] - cpu.registers[(opcode & 0x0F00) >> 8];
                    break;
                case 0x000E: //0x8XY5: Set VX equal to VX multipied by 2, set VF to MSB of VX
                    cpu.registers[0xF] = cpu.registers[(opcode & 0x0F00) >> 8] & 0b10000000;
                    cpu.registers[(opcode & 0x0F00) >> 8] *= 2;
                    break;
                default:
                    std::cout << "Unknown opcode: 0x" << opcode << std::endl;
                    break;
                    
                cpu.pc += 2;
                break;
            }
        default:
            std::cout << "Unknown opcode: 0x" << opcode << std::endl;
            break;
    }
}

bool Chip8::GetPixel(uint16_t index) {
    return display.GetPixel(index);
} 