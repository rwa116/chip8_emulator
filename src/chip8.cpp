#include "chip8.hpp"

Chip8::Chip8() {
    memory = Memory();
    cpu = CPU();
    display = Display();
    input = Input();
    opcode = 0;
}

/**
 * Loads a program into memory.
 * @param buffer The buffer containing the program to load.
 * @param size The size of the program to load.
 */
void Chip8::LoadProgram(uint8_t* buffer, int size) {
    memory.LoadProgram(buffer, size);
}

/**
 * Decrements the delay and sound timers.
*/
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

/**
 * Sends input to the emulator.
 * @param code The keycode of the key pressed.
 * @param state The state of the key (pressed or released).
 */
void Chip8::SendInput(SDL_Keycode code, bool state) {
    switch(code) {
        case SDLK_1:
            input.SetKeyState(0x1, state);
            break;
        case SDLK_2:
            input.SetKeyState(0x2, state);
            break;
        case SDLK_3:
            input.SetKeyState(0x3, state);
            break;
        case SDLK_4:
            input.SetKeyState(0xC, state);
            break;
        case SDLK_q:
            input.SetKeyState(0x4, state);
            break;
        case SDLK_w:
            input.SetKeyState(0x5, state);
            break;
        case SDLK_e:
            input.SetKeyState(0x6, state);
            break;
        case SDLK_r:
            input.SetKeyState(0xD, state);
            break;
        case SDLK_a:
            input.SetKeyState(0x7, state);
            break;
        case SDLK_s:
            input.SetKeyState(0x8, state);
            break;
        case SDLK_d:
            input.SetKeyState(0x9, state);
            break;
        case SDLK_f:
            input.SetKeyState(0xE, state);
            break;
        case SDLK_z:
            input.SetKeyState(0xA, state);
            break;
        case SDLK_x:
            input.SetKeyState(0x0, state);
            break;
        case SDLK_c:
            input.SetKeyState(0xB, state);
            break;
        case SDLK_v:
            input.SetKeyState(0xF, state);
            break;
    }
}

/**
 * Recieves input from the emulator.
 * @param code The keycode of the key input to receive.
*/
bool Chip8::RecieveInput(SDL_Keycode code) {
    switch(code) {
        case SDLK_1:
            return input.GetKeyState(0x1);
            break;
        case SDLK_2:
            return input.GetKeyState(0x2);
            break;
        case SDLK_3:
            return input.GetKeyState(0x3);
            break;
        case SDLK_4:
            return input.GetKeyState(0xC);
            break;
        case SDLK_q:
            return input.GetKeyState(0x4);
            break;
        case SDLK_w:
            return input.GetKeyState(0x5);
            break;
        case SDLK_e:
            return input.GetKeyState(0x6);
            break;
        case SDLK_r:
            return input.GetKeyState(0xD);
            break;
        case SDLK_a:
            return input.GetKeyState(0x7);
            break;
        case SDLK_s:
            return input.GetKeyState(0x8);
            break;
        case SDLK_d:
            return input.GetKeyState(0x9);
            break;
        case SDLK_f:
            return input.GetKeyState(0xE);
            break;
        case SDLK_z:
            return input.GetKeyState(0xA);
            break;
        case SDLK_x:
            return input.GetKeyState(0x0);
            break;
        case SDLK_c:
            return input.GetKeyState(0xB);
            break;
        case SDLK_v:
            return input.GetKeyState(0xF);
            break;
        default:
            return false;
            break;
    }
}

/**
 * Executes one cycle of the emulator.
 */
void Chip8::Tick() {
    opcode = memory.FetchOpcode(cpu.pc);

    // Decode opcode
    //std::cout << "Opcode: " << opcode << ", PC = " << cpu.pc << std::endl;
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
            switch (opcode & 0x00FF) {
            case 0x009E: // 0xEX9E: Skips the next instruction if the key stored in VX is pressed
                if (input.GetKeyState(cpu.registers[(opcode & 0x0F00) >> 8])) {
                    cpu.pc += 4;
                } else {
                    cpu.pc += 2;
                }
                break;
            case 0x00A1: // 0xEXA1: Skips the next instruction if the key stored in VX isn't pressed
                if (!input.GetKeyState(cpu.registers[(opcode & 0x0F00) >> 8])) {
                    cpu.pc += 4;
                } else {
                    cpu.pc += 2;
                }
                break;
            default:
                cpu.pc += 2;
                break;
            }
            break;
        case 0xF000:
            switch(opcode & 0x00FF) {
                case 0x0007: // 0xFX07: Set VX equal to the value of the delay timer
                    cpu.registers[(opcode & 0x0F00) >> 8] = cpu.delayTimer;
                    cpu.pc += 2;
                    break;
                case 0x000A: // 0xFX0A: Wait for a key press, store the value of the key in VX
                    for (int i = 0; i < 16; i++) {
                        if (input.GetKeyState(i)) {
                            cpu.registers[(opcode & 0x0F00) >> 8] = i;
                            cpu.pc += 2;
                        }
                    }
                    break;
                case 0x0015: // 0xFX15: Set the delay timer equal to VX
                    cpu.delayTimer = cpu.registers[(opcode & 0x0F00) >> 8];
                    cpu.pc += 2;
                    break;
                case 0x0018: // 0xFX18: Set the sound timer equal to VX
                    cpu.soundTimer = cpu.registers[(opcode & 0x0F00) >> 8];
                    cpu.pc += 2;
                    break;
                case 0x001E: // 0xFX1E: Set I equal to I plus VX
                    cpu.I += cpu.registers[(opcode & 0x0F00) >> 8];
                    cpu.pc += 2;
                    break;
                case 0x0029: // 0xFX29: Set I equal to the location of the sprite for the character in VX
                    cpu.I = cpu.registers[(opcode & 0x0F00) >> 8] * 0x5;
                    cpu.pc += 2;
                    break;
                case 0x0033: // 0xFX33: Store the binary-coded decimal equivalent of VX at the addresses I, I plus 1, and I plus 2
                    memory.SetMem(cpu.I, cpu.registers[(opcode & 0x0F00) >> 8] / 100);
                    memory.SetMem(cpu.I + 1, (cpu.registers[(opcode & 0x0F00) >> 8] / 10) % 10);
                    memory.SetMem(cpu.I + 2, (cpu.registers[(opcode & 0x0F00) >> 8] % 100) % 10);
                    cpu.pc += 2;
                    break;
                case 0x0055: // 0xFX55: Store V0 to VX in memory starting at address I
                    for (int i = 0; i <= ((opcode & 0x0F00) >> 8); i++) {
                        memory.SetMem(cpu.I + i, cpu.registers[i]);
                    }
                    cpu.pc += 2;
                    break;
                case 0x0065: // 0xFX65: Fill V0 to VX with values from memory starting at address I
                    for (int i = 0; i <= ((opcode & 0x0F00) >> 8); i++) {
                        cpu.registers[i] = memory.GetMem(cpu.I + i);
                    }
                    cpu.pc += 2;
                    break;
            }
            break;
        default:
            std::cout << "Unknown opcode: 0x" << opcode << std::endl;
            break;
    }
}

/**
 * Gets the state of a pixel in the display.
 * @param index The index of the pixel to get the state of
 */
bool Chip8::GetPixel(uint16_t index) {
    return display.GetPixel(index);
} 