#include "emulator.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

Emulator::Emulator() {
    graphics = Graphics();
    chip8 = Chip8();
}

Emulator::~Emulator() {

}

bool Emulator::Init(char argc, char* argv[]) {
    if(argc != 2) {
        std::cerr << "Usage: chip8 <ROM file>" << std::endl;
        return false;
    }

    //Open file and read into buffer
    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << argv[1] << std::endl;
        return false;
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    chip8.LoadProgram((uint8_t*)buffer.str().c_str(), buffer.str().length());

    if (!graphics.Init()) {
        return false;
    }

    graphics.Clear();
    return true;
}

/**
 * Main run loop for the emulator.
*/
void Emulator::Run() {
    while(isRunning()) {
        SDL_Delay(1000/60); // 16.67 ms per frame (60hz)
        // Update window
        graphics.PollEvents();
        //graphics.Update();
        // Draw to screen
        Draw();
        chip8.Tick();
    }
}

/**
 * Draws the current state of the display to the screen.
*/
void Emulator::Draw() {
    graphics.Clear();
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 32; j++) {
            if (chip8.GetPixel(i + j*64)) {
                graphics.SetPixel(i, j, true);
            }
        }
    }
}

bool Emulator::isRunning() {
    return graphics.isRunning();
}