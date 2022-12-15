#include "simple_canvas.hpp"
#include "app.hpp"

SimpleCanvas::SimpleCanvas(booba::Tool* connectedTool, const Rect& bounds, Widget* parent):
	Widget(bounds, parent),
	m_connectedTool(connectedTool)
{

}

SimpleCanvas::~SimpleCanvas()
{

}

void SimpleCanvas::setPixel(uint32_t x, uint32_t y, uint32_t color)
{
	m_drawingSurface.setPixel(x, y, color);
}

void SimpleCanvas::blit(Surface* surface, const Rect& bounds)
{
	int w = surface->getWidth();
	int h = surface->getHeight();

	for (int y = 0; y < std::min(h, bounds.h); y++) {
		for (int x = 0; x < std::min(w, bounds.w); x++) {
			m_drawingSurface.setPixel(bounds.x + x, bounds.y + y, surface->getPixel(x, y));
		}
	}
}

void SimpleCanvas::draw()
{
	Texture* pictureTex = new Texture(m_drawingSurface);
	Rect copyBounds = {0, 0, m_drawingSurface.getWidth(), m_drawingSurface.getHeight()};

	Renderer* renderer = getApp()->getRenderer();
	renderer->copyTexture(pictureTex, this->getRealBounds(), copyBounds);

	delete pictureTex;
}

bool SimpleCanvas::intersects(const Vec2& point)
{
	if (point.getX() < m_bounds.x || 
		point.getX() > m_bounds.x + m_bounds.w)
	{
		return false;
	}

	if (point.getY() < m_bounds.y || 
		point.getY() > m_bounds.y + m_bounds.h)
	{
		return false;
	}

	return true;
}

bool SimpleCanvas::onMouseMove(const Vec2& point, const Vec2& motion)
{
	if (m_isHidden) {
		return false;
	}

	if (!m_connectedTool) {
		return false;
	}

	booba::Event genEvent = {};
	genEvent.type = booba::EventType::CanvasMMoved;

	genEvent.Oleg.cedata.id = reinterpret_cast<uint64_t>(this);
	genEvent.Oleg.cedata.x  = static_cast<int32_t>(point.getX());
	genEvent.Oleg.cedata.y  = static_cast<int32_t>(point.getY());

	m_connectedTool->apply(nullptr, &genEvent);
}

bool SimpleCanvas::onButtonClick(MouseButton button, const Vec2& point)
{
	if (m_isHidden) {
		return false;
	}

	if (!m_connectedTool) {
		return false;
	}

	booba::Event genEvent = {};
	genEvent.type = booba::EventType::CanvasMPressed;
	
	genEvent.Oleg.cedata.id = reinterpret_cast<uint64_t>(this);
	genEvent.Oleg.cedata.x  = static_cast<int32_t>(point.getX());
	genEvent.Oleg.cedata.y  = static_cast<int32_t>(point.getY());

	m_connectedTool->apply(nullptr, &genEvent);
}

bool SimpleCanvas::onButtonRelease(MouseButton button, const Vec2& point)
{
	if (m_isHidden) {
		return false;
	}

	if (!m_connectedTool) {
		return false;
	}

	booba::Event genEvent = {};
	genEvent.type = booba::EventType::CanvasMReleased;
	
	genEvent.Oleg.cedata.id = reinterpret_cast<uint64_t>(this);
	genEvent.Oleg.cedata.x  = static_cast<int32_t>(point.getX());
	genEvent.Oleg.cedata.y  = static_cast<int32_t>(point.getY());

	m_connectedTool->apply(nullptr, &genEvent);
}

bool SimpleCanvas::onKeyPress(Key key)
{
	if (m_isHidden) {
		return false;
	}
}

bool SimpleCanvas::onKeyRelease(Key key)
{
	if (m_isHidden) {
		return false;
	}
}

bool SimpleCanvas::onTick(Time time)
{
	if (m_isHidden) {
		return false;
	}

	this->draw();
	return true;
}
