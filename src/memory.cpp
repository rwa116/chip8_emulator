#include "memory.hpp"

Memory::Memory() {
    // Initialize memory
    for(int i = 0; i < 4096; i++) {
        memory[i] = 0;
    }
    // Initialize sprites
    // uint8_t sprites[] = {
    //     0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    //     0x20, 0x60, 0x20, 0x20, 0x70, // 1
    //     0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    //     0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    //     0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    //     0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    //     0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    //     0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    //     0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    //     0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    //     0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    //     0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    //     0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    //     0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    //     0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    //     0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    // };
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