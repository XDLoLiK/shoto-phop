#ifndef CURSOR_HPP
#define CURSOR_HPP

#include <SDL2/SDL.h>

using Cursor = SDL_Cursor;

Cursor* getCursor();

void hideCursor();
void showCursor();

#endif // CURSOR_HPP
