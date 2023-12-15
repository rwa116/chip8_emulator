#include "display.hpp"

Display::Display() {
    for (int i = 0; i < 64 * 32; i++) {
        display[i] = 0;
    }
}

/**
 * Clears the display.
 
*/
void Display::Clear() {
    for (int i = 0; i < 64 * 32; i++) {
        display[i] = 0;
    }
}

/**
 * Gets the pixel at the given index.
 * @param index the index of the pixel.
*/
bool Display::GetPixel(uint16_t index) {
    return display[index];
}