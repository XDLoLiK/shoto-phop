#ifndef EVENT_HPP
#define EVENT_HPP

#include <SDL2/SDL.h>

using Time        = uint32_t;
using MouseButton = uint8_t;
using Key         = SDL_Keycode;

class Event
{
public:
	Event()
	{

	}

	~Event()
	{

	}

	int poll()
	{
		return SDL_PollEvent(&m_realEvent);
	}

	const SDL_Event* getRealEvent() const
	{
		return &m_realEvent;
	}

private:
	SDL_Event m_realEvent = {};
};

#endif // EVENT_HPP
