#ifndef INPUT_H
#define INPUT_H

#include "SDL.h"

class Input {
    public:
        Input();
        bool GetKeyState(int key);
        void SetKeyState(int key, bool state);
        bool AnyKeyActive();
        void SetKeyActive(bool state);
    private:
        bool keys[16];
        bool keyActive;
};

#endif // INPUT_H