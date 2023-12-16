#ifndef CHIP8_H
#define CHIP8_H

#include "memory.hpp"
#include "cpu.hpp"
#include "display.hpp"
#include "input.hpp"
#include <stdlib.h>
#include <iostream>

class Chip8 {
    public:
        Chip8();
        void LoadProgram(uint8_t* buffer, int size);
        bool TimerTick();
        void Tick();
        bool GetPixel(uint16_t index);
        bool RecieveInput(SDL_Keycode code);
        void SendInput(SDL_Keycode code, bool state);
    private:
        Memory memory;
        CPU cpu;
        Display display;
        Input input;
        uint16_t opcode;
};

#endif // CHIP8_H