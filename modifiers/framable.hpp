#ifndef FRAMABLE_HPP
#define FRAMABLE_HPP

#include <SDL2/SDL.h>

#include "color.hpp"
#include "renderer.hpp"

class Framable
{
public:
	Framable();
	virtual ~Framable();

	void setFrameColor       (const Color& color);
	void setFrameColorDefault(const Color& color);
	void setFrameColorHover  (const Color& color);

protected:
	void drawFrame(const Rect& bounds, bool isHovered = false);

protected:
	bool m_colorChanged = true;

	Color m_frameColorDefault = {0, 0, 0, 0};
	Color m_frameColorHover   = {0, 0, 0, 0};
};

#endif // FRAMABLE_HPP
