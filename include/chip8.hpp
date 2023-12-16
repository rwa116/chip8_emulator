#ifndef CHIP8_H
#define CHIP8_H

#include "memory.hpp"
#include "cpu.hpp"
#include "display.hpp"
#include <stdlib.h>
#include <iostream>

class Chip8 {
    public:
        Chip8();
        void LoadProgram(uint8_t* buffer, int size);
        void TimerTick();
        void Tick();
        bool GetPixel(uint16_t index);
    private:
        Memory memory;
        CPU cpu;
        Display display;
        uint16_t opcode;
};

#endif // CHIP8_H