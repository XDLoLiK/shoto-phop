#include "framable.hpp"
#include "app.hpp"


extern App* __theApp__;


Framable::Framable(const Color& color):
	m_frameColor(color)
{

}

Framable::~Framable()
{
	m_frameColor = {255, 255, 255, 255};
}

void Framable::setFrameColor(const Color& color)
{
	m_frameColor = color;
}

void Framable::drawFrame(const Rect& bounds)
{
	Renderer* renderer = __theApp__->getRenderer();
	renderer->setDrawColor(m_frameColor);
	
	renderer->drawLine(bounds.x, bounds.y, bounds.x + bounds.w, bounds.y);
	renderer->drawLine(bounds.x, bounds.y, bounds.x, bounds.y + bounds.h);

	renderer->drawLine(bounds.x + bounds.w, bounds.y + bounds.h, 
		               bounds.x, bounds.y + bounds.h);
	renderer->drawLine(bounds.x + bounds.w, bounds.y + bounds.h, 
		               bounds.x + bounds.w, bounds.y);
}
