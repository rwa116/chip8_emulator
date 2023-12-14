#include "graphics.hpp"
#include <iostream>

Graphics::Graphics() {
    window = NULL;
    renderer = NULL;
    texture = NULL;
    running = false;
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 32; j++) {
            pixels[i][j] = false;
        }
    }
}

/**
 * Deallocates memory and quits SDL.
*/
Graphics::~Graphics() {
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

/**
 * Initializes SDL and creates a window, renderer, and texture.
 * @return true if successful, false otherwise.
*/
bool Graphics::Init() {
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }
    window = SDL_CreateWindow("Chip8", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH*SCREEN_SCALE, SCREEN_HEIGHT*SCREEN_SCALE, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
    running = true;
    // check for errors in window, renderer, and texture creation
    if(window == NULL) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return false;
    }
    if(renderer == NULL) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        return false;
    }
    // TODO: check for errors in texture creation
    return true;
}

void Graphics::Clear() {
    SDL_SetRenderDrawColor(renderer, white >> 24, (white >> 16) & 0xFF, (white >> 8) & 0xFF, white & 0xFF);
    SDL_RenderClear(renderer);
}

void Graphics::Update() {
    SDL_RenderPresent(renderer);
}

void Graphics::PollEvents() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                break;
            case SDL_KEYUP:
                break;
            default:
                break;
        }
    }
}

bool Graphics::isRunning() {
    return running;
}