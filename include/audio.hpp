#ifndef AUDIO_H
#define AUDIO_H

#include "SDL.h"
#include <iostream>

class Audio {
    public:
        Audio();
        ~Audio();
        bool Init();
        void Play();
        void Stop();
    private:
        SDL_AudioSpec want, have;
        SDL_AudioDeviceID device;
        uint8_t *buffer;
};

#endif // AUDIO_H