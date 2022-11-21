#include "cursor.hpp"

Cursor* getCursor()
{
	return SDL_GetCursor();
}

void hideCursor()
{
	SDL_ShowCursor(SDL_DISABLE);
}

void showCursor()
{
	SDL_ShowCursor(SDL_ENABLE);
}
