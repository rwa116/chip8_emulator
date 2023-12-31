#include "input.hpp"

Input::Input() {
    for(int i = 0; i < 16; i++) {
        keys[i] = false;
    }
    keyActive = false;
}

/**
 * Gets the state of the specified key.
 * @param key the key to get the state of.
 */
bool Input::GetKeyState(int key) {
    return keys[key];
}

/**
 * Sets the state of the specified key.
 * @param key the key to set the state of.
 * @param state the state to set the key to.
 */
void Input::SetKeyState(int key, bool state) {
    keys[key] = state;
}

/**
 * Checks if any key is currently active.
 */
bool Input::AnyKeyActive() {
    return keyActive;
}

/**
 * Sets the state of the keyActive variable.
 * @param state the state to set keyActive to.
 */
void Input::SetKeyActive(bool state) {
    keyActive = state;
}