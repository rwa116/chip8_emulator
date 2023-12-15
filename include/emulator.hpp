#ifndef EMULATOR_H
#define EMULATOR_H

#include "graphics.hpp"
#include "chip8.hpp"

class Emulator {
    public:
        Emulator();
        ~Emulator();
        bool Init(char argc, char* argv[]);
        void Run();
        void Draw();
    private:
        bool isRunning();
        Chip8 chip8;
        Graphics graphics;
};

#endif // EMULATOR_H