#include "emulator.hpp"
#include <iostream>

Emulator::Emulator() {
    graphics = Graphics();
}

Emulator::~Emulator() {

}

bool Emulator::Init() {
    if(!graphics.Init()) {
        return false;
    }

    graphics.Clear();
    return true;
}

void Emulator::Run() {
    while(isRunning()) {
        SDL_Delay(1000/60); // 16.67 ms per frame (60hz)
        // Update window
        graphics.PollEvents();
        graphics.Update();
    }
}

bool Emulator::isRunning() {
    return graphics.isRunning();
}