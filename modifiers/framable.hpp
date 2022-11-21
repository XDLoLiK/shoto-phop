#ifndef FRAMABLE_HPP
#define FRAMABLE_HPP

#include <SDL2/SDL.h>

#include "color.hpp"
#include "renderer.hpp"

class Framable
{
public:
	Framable(const Color& color = {0, 0, 0, 0});
	virtual ~Framable();

	void setFrameColor(const Color& color);

protected:
	void drawFrame(const Rect& bounds);

protected:
	Color m_frameColor = {0, 0, 0, 0};
};

#endif // FRAMABLE_HPP
