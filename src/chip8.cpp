#include "chip8.hpp"

Chip8::Chip8() {
    memory = Memory();
    cpu = CPU();
    opcode = 0;
}

void Chip8::LoadProgram(uint8_t* buffer, int size) {
    memory.LoadProgram(buffer, size);
}

void Chip8::Tick() {
    opcode = memory.FetchOpcode(cpu.pc);
}

bool Chip8::GetPixel(uint16_t index) {
    return display.GetPixel(index);
} 