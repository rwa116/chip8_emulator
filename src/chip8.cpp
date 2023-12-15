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
        default:
            std::cout << "Unknown opcode: 0x" << opcode << std::endl;
            break;
    }
}

bool Chip8::GetPixel(uint16_t index) {
    return display.GetPixel(index);
} 