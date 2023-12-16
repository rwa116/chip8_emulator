#ifndef INPUT_H
#define INPUT_H

#include "SDL.h"

class Input {
    public:
        Input();
        bool GetKeyState(int key);
        void SetKeyState(int key, bool state);
    private:
        bool keys[16];
};

#endif // INPUT_H