#include "memory.hpp"

Memory::Memory() {
    // Initialize memory
    for(int i = 0; i < 4096; i++) {
        memory[i] = 0;
    }
    std::copy(sprites, sprites + 80, memory);
}

/**
 * Loads a program into memory.
*/
void Memory::LoadProgram(uint8_t* buffer, int size) {
    // Load program into memory starting at address 0x200
    for(int i = 0; i < size; i++) {
        memory[PROGRAM_START + i] = buffer[i];
    }
}

/**
 * Gets the value at the specified address.
*/
uint8_t Memory::GetMem(uint16_t address) {
    return memory[address];
}

/**
 * Sets the value at the specified address.
*/
void Memory::SetMem(uint16_t address, uint8_t value) {
    memory[address] = value;
}

/**
 * Gets the sprite at the specified index.
*/
uint8_t Memory::GetSprite(uint8_t address) {
    return sprites[address];
}

/**
 * Fetches the opcode at the specified address.
*/
uint16_t Memory::FetchOpcode(uint16_t pc) {
    uint16_t opcode = memory[pc] << 8 | memory[pc + 1];
    return opcode;
}