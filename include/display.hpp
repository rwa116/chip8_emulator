#ifndef DISPLAY_H
#define DISPLAY_H

#include <cstdint>

class Display {
    public:
        Display();
        void Clear();
        bool GetPixel(uint16_t index);
    private:
        bool display[64 * 32];
};

#endif // DISPLAY_H