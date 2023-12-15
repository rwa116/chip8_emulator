#include <iostream>
#include "graphics.hpp"
#include "emulator.hpp"
#include "SDL.h"

int main(int argc, char* argv[]) {

    Emulator emulator = Emulator();

    if(!emulator.Init(argc, argv)) {
        return -1;
    }

    emulator.Run();

    return 0;
}

