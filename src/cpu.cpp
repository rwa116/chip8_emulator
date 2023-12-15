#include "cpu.hpp"

CPU::CPU() {
    pc = 0x200;
    sp = 0;
    delayTimer = 0;
    soundTimer = 0;
    for (int i = 0; i < 16; i++) {
        registers[i] = 0;
        stack[i] = 0;
        keypad[i] = 0;
    }
}