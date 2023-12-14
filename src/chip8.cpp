#include <iostream>
#include "graphics.hpp"
#include "emulator.hpp"
#include "SDL.h"

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;

    Emulator emulator = Emulator();

    if(!emulator.Init()) {
        return -1;
    }

    emulator.Run();

    return 0;
}

