#ifndef CPU_H
#define CPU_H

#include <cstdint>

class CPU {
    public:
        CPU();
        uint8_t registers[16];
        uint16_t pc;
        uint16_t stack[16];
        uint8_t sp;
        uint16_t I;
        uint8_t delayTimer;
        uint8_t soundTimer;
    private:
        uint8_t keypad[16];
};

#endif // CPU_H