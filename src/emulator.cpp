#include "emulator.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#define STEP_MODE false

Emulator::Emulator() {
    graphics = Graphics();
    audio = Audio();
    chip8 = Chip8();
    running = false;
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

    if(!audio.Init()) {
        return false;
    }

    graphics.Clear();
    running = true;
    return true;
}

/**
 * Main run loop for the emulator.
*/
void Emulator::Run() {
    while(running) {
        SDL_Delay(1000/60); // 16.67 ms per frame (60hz)
        // Update window
        PollEvents();
        // Run cpu cycles
        for(uint8_t i=0; i<10; i++) {
            chip8.Tick(); // 10 cpu cycles per frame
        }
        // Draw to screen
        Draw();
        graphics.Update();

        // // Update timers
        bool playSound = chip8.TimerTick();

        if(playSound) {
            audio.Play();
        } else {
            audio.Stop();
        }

        if(STEP_MODE) {
            std::cout << "Press enter to continue..." << std::endl;
            std::cin.get();
        }
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

/**
 * Polls for events and handles them.
*/
void Emulator::PollEvents() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                chip8.SendInput(event.key.keysym.sym, true);
                break;
            case SDL_KEYUP:
                chip8.SendInput(event.key.keysym.sym, false);
                break;
            default:
                break;
        }
    }
}