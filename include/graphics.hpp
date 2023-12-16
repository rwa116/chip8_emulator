#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "SDL.h"

#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32
#define SCREEN_SCALE 10

class Graphics {
    public:
        Graphics();
        ~Graphics();
        bool Init();
        void Clear();
        void Draw();
        void Update();
        void SetPixel(int x, int y, bool value);
        bool GetPixel(int x, int y);
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Texture* texture;
        bool running;
        bool pixels[SCREEN_WIDTH][SCREEN_HEIGHT];
        uint32_t white = 0xFFFFFFFF;
        uint32_t black = 0x00000000;
};


#endif // GRAPHICS_H