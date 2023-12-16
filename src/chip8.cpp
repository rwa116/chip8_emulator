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

void Chip8::TimerTick() {
    if (cpu.delayTimer > 0) {
        cpu.delayTimer--;
    }
    if (cpu.soundTimer > 0) {
        if (cpu.soundTimer == 1) {
            std::cout << "BEEP!" << std::endl; //TODO: Implement sound
        }
        cpu.soundTimer--;
    }
}

void Chip8::Tick() {
    opcode = memory.FetchOpcode(cpu.pc);

    // Decode opcode
    std::cout << "Opcode: " << opcode << ", PC = " << cpu.pc << std::endl;
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
            }
            cpu.pc += 2;
            break;
        case 0x9000: // 0x9XY0: Skips the next instruction if VX doesn't equal VY
            if (cpu.registers[(opcode & 0x0F00) >> 8] != cpu.registers[(opcode & 0x00F0) >> 4]) {
                cpu.pc += 4;
            } else {
                cpu.pc += 2;
            }
            break;
        case 0xA000: // 0xANNN: Set I equal to NNN
            cpu.I = opcode & 0x0FFF;
            cpu.pc += 2;
            break;
        case 0xB000: // 0xBNNN: Jump to address NNN plus V0
            cpu.pc = (opcode & 0x0FFF) + cpu.registers[0];
            break;
        case 0xC000: // 0xCXNN: Set VX equal to the result of a bitwise AND operation on a random number and NN
            cpu.registers[(opcode & 0x0F00) >> 8] = (rand() % 256) & (opcode & 0x00FF);
            cpu.pc += 2;
            break;
        case 0xD000: // 0xDXYN: Draw a sprite at position VX, VY with N bytes of sprite data starting at the address stored in I
            {
                uint8_t x = cpu.registers[(opcode & 0x0F00) >> 8];
                uint8_t y = cpu.registers[(opcode & 0x00F0) >> 4];
                uint8_t height = opcode & 0x000F;
                uint8_t pixel;

                cpu.registers[0xF] = 0;
                for (int yline = 0; yline < height; yline++) {
                    pixel = memory.GetMem(cpu.I + yline);
                    for (int xline = 0; xline < 8; xline++) {
                        if ((pixel & (0x80 >> xline)) != 0) {
                            if (display.GetPixel((x + xline + ((y + yline) * 64)))) {
                                cpu.registers[0xF] = 1;
                            }
                            display.SetPixel(x + xline + ((y + yline) * 64), !display.GetPixel(x + xline + ((y + yline) * 64)));
                        }
                    }
                }
                cpu.pc += 2;
                break;
            }
        case 0xE000:
            std::cout << "Key press not implemented yet" << std::endl;
            cpu.pc += 2;
            break;
        case 0xF000:
            switch(opcode & 0x00FF) {
                case 0x0007: // 0xFX07: Set VX equal to the value of the delay timer
                    cpu.registers[(opcode & 0x0F00) >> 8] = cpu.delayTimer;
                    break;
                case 0x000A: // 0xFX0A: Wait for a key press, store the value of the key in VX
                    std::cout << "Key press not implemented yet" << std::endl;
                    break;
                case 0x0015: // 0xFX15: Set the delay timer equal to VX
                    cpu.delayTimer = cpu.registers[(opcode & 0x0F00) >> 8];
                    break;
                case 0x0018: // 0xFX18: Set the sound timer equal to VX
                    cpu.soundTimer = cpu.registers[(opcode & 0x0F00) >> 8];
                    break;
                case 0x001E: // 0xFX1E: Set I equal to I plus VX
                    cpu.I += cpu.registers[(opcode & 0x0F00) >> 8];
                    break;
                case 0x0029: // 0xFX29: Set I equal to the location of the sprite for the character in VX
                    std::cout << "Sprite location not implemented yet" << std::endl;
                    break;
                case 0x0033: // 0xFX33: Store the binary-coded decimal equivalent of VX at the addresses I, I plus 1, and I plus 2
                    memory.SetMem(cpu.I, cpu.registers[(opcode & 0x0F00) >> 8] / 100);
                    memory.SetMem(cpu.I + 1, (cpu.registers[(opcode & 0x0F00) >> 8] / 10) % 10);
                    memory.SetMem(cpu.I + 2, (cpu.registers[(opcode & 0x0F00) >> 8] % 100) % 10);
                    break;
                case 0x0055: // 0xFX55: Store V0 to VX in memory starting at address I
                    for (int i = 0; i <= ((opcode & 0x0F00) >> 8); i++) {
                        memory.SetMem(cpu.I + i, cpu.registers[i]);
                    }
                    break;
                case 0x0065: // 0xFX65: Fill V0 to VX with values from memory starting at address I
                    for (int i = 0; i <= ((opcode & 0x0F00) >> 8); i++) {
                        cpu.registers[i] = memory.GetMem(cpu.I + i);
                    }
                    break;
            }
            cpu.pc += 2;
            break;
        default:
            std::cout << "Unknown opcode: 0x" << opcode << std::endl;
            break;
    }
}

bool Chip8::GetPixel(uint16_t index) {
    return display.GetPixel(index);
} 