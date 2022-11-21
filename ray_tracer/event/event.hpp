#pragma once

#include <SDL2/SDL.h>

/* Wrapper around SDL event */
class Event {
private:
    unsigned type_ = SDL_QUIT;

    SDL_KeyboardEvent    key_    = {};
    SDL_MouseMotionEvent motion_ = {};
    SDL_MouseButtonEvent button_ = {};
    SDL_MouseWheelEvent  wheel_  = {};

public:
    Event();

    int poll();

    /* Getters */
    unsigned type() const;
    SDL_KeyboardEvent    key()    const;
    SDL_MouseMotionEvent motion() const;
    SDL_MouseButtonEvent button() const;
    SDL_MouseWheelEvent  wheel()  const;
};
