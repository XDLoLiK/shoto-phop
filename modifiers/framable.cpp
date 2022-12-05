#include "framable.hpp"
#include "app.hpp"

static inline bool operator==(const Rect& first, const Rect& second)
{
	return (first.x == second.x && first.y == second.y &&
		    first.w == second.w && first.h == second.h);
}

Framable::Framable()
{

}

Framable::~Framable()
{

}

void Framable::setFrameColor(const Color& color)
{
	m_frameColorDefault = color;
	m_frameColorHover   = color;
	m_colorChanged = true;
}

void Framable::setFrameColorDefault(const Color& color)
{
	m_frameColorDefault = color;
	m_colorChanged = true;
}

void Framable::setFrameColorHover(const Color& color)
{
	m_frameColorHover = color;
	m_colorChanged = true;
}

void Framable::drawFrame(const Rect& bounds, bool isHovered)
{
	static Rect oldBounds  = {0, 0, 0, 0};
	static bool hoverState = false;

	if (!m_colorChanged && oldBounds == bounds && isHovered == hoverState) {
		return;
	}

	Renderer* renderer = getApp()->getRenderer();
	renderer->setDrawColor(isHovered ? m_frameColorHover : m_frameColorDefault);
	
	renderer->drawLine(bounds.x, bounds.y, bounds.x + bounds.w, bounds.y);
	renderer->drawLine(bounds.x, bounds.y, bounds.x, bounds.y + bounds.h);
	renderer->drawLine(bounds.x + bounds.w, bounds.y + bounds.h, bounds.x, bounds.y + bounds.h);
	renderer->drawLine(bounds.x + bounds.w, bounds.y + bounds.h, bounds.x + bounds.w, bounds.y);

	oldBounds  = bounds;
	hoverState = isHovered;
	m_colorChanged = false;
}
