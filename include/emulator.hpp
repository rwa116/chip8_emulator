#ifndef EMULATOR_H
#define EMULATOR_H

#include "graphics.hpp"

class Emulator {
    public:
        Emulator();
        ~Emulator();
        bool Init();
        void Run();
    private:
        bool isRunning();
        Graphics graphics;
};

#endif // EMULATOR_H