#include "audio.hpp"

Audio::Audio() {
    buffer = NULL;
    device = 0;
}

/**
 * Closes the audio device
 */
Audio::~Audio() {
    SDL_CloseAudioDevice(device);
}

/**
 * Callback function for SDL audio.
 * @param userdata
 * @param stream
 * @param len
 */
void Callback(void *userdata, uint8_t *stream, int len) {
    (void)userdata;

    int16_t *buffer = (int16_t*)stream;
    static uint32_t sample_index = 0;
    const int32_t square_wave_period = 44100 / 440;
    
    for(int i = 0; i < len / 2; i++) {
        if(sample_index++ % square_wave_period < square_wave_period / 2) {
            buffer[i] = 0x03E8;
        } else {
            buffer[i] = 0x0000;
        }
    }
}

/**
 * Initializes SDL audio and loads the beep sound.
 * @return true if successful, false otherwise.
 */
bool Audio::Init() {
    if(SDL_Init(SDL_INIT_AUDIO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }

    want = (SDL_AudioSpec){
        .freq = 44100,
        .format = AUDIO_S16LSB,
        .channels = 1,
        .silence = 0,
        .samples = 4096,
        .padding = 0,
        .size = 0,
        .callback = Callback,
        .userdata = NULL
    };

    device = SDL_OpenAudioDevice(NULL, 0, &want, &have, 0);
    if(device == 0) {
        std::cerr << "SDL_OpenAudioDevice Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void Audio::Play() {
    SDL_PauseAudioDevice(device, 0);
}

void Audio::Stop() {
    SDL_PauseAudioDevice(device, 1);
}