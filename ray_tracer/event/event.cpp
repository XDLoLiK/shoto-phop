#include "event.hpp"

Event::Event()
{

}

int Event::poll()
{
    SDL_Event event = {};
    int ret = SDL_PollEvent(&event);

    type_   = event.type;
    key_    = event.key;
    motion_ = event.motion;
    button_ = event.button;
    wheel_  = event.wheel;

    return ret;
}

unsigned Event::type() const
{
    return type_;
}

SDL_KeyboardEvent Event::key() const
{
    return key_;
}

SDL_MouseMotionEvent Event::motion() const
{
    return motion_;
}

SDL_MouseButtonEvent Event::button() const
{
    return button_;
}

SDL_MouseWheelEvent Event::wheel() const
{
    return wheel_;
}
