#include "simple_canvas.hpp"
#include "app.hpp"

SimpleCanvas::SimpleCanvas(booba::Tool* connectedTool, const Rect& bounds, Widget* parent):
	Widget(bounds, parent),
	m_connectedTool(connectedTool)
{
	m_drawingSurface = Surface(bounds.w, bounds.h);
	m_curTexture = new Texture(m_drawingSurface);
}

SimpleCanvas::~SimpleCanvas()
{

}

void SimpleCanvas::setPixel(size_t x, size_t y, uint32_t color)
{
	m_drawingSurface.setPixel(x, y, color);
	m_changed = true;
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

	m_changed = true;
}

void SimpleCanvas::fillColor(uint32_t color)
{
	m_drawingSurface.fillColor(Color(color));
	m_changed = true;
}

void SimpleCanvas::draw()
{
	if (m_changed) {
		m_changed = false;
		delete m_curTexture;
		m_curTexture = new Texture(m_drawingSurface);
	}

	if (!m_curTexture) {
		return;
	}

	Rect copyBounds = {0, 0, m_curTexture->getBounds().w, m_curTexture->getBounds().h};
	Renderer* renderer = getApp()->getRenderer();
	renderer->copyTexture(m_curTexture, this->getRealBounds(), copyBounds);
}

bool SimpleCanvas::intersects(const Vec2& point)
{
	const Rect& bounds = this->getRealBounds();

	if (point.getX() < bounds.x || 
		point.getX() > bounds.x + bounds.w)
	{
		return false;
	}

	if (point.getY() < bounds.y || 
		point.getY() > bounds.y + bounds.h)
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

	if (this->intersects(point)) {
		const Rect& bounds = this->getRealBounds();

		booba::Event genEvent = {};
		genEvent.type = booba::EventType::CanvasMMoved;

		genEvent.Oleg.cedata.id = reinterpret_cast<uint64_t>(this);
		genEvent.Oleg.cedata.x  = static_cast<size_t>(point.getX() - bounds.x);
		genEvent.Oleg.cedata.y  = static_cast<size_t>(point.getY() - bounds.y);

		m_connectedTool->apply(nullptr, &genEvent);
	}
}

bool SimpleCanvas::onButtonClick(MouseButton button, const Vec2& point)
{
	if (m_isHidden) {
		return false;
	}

	if (!m_connectedTool) {
		return false;
	}

	if (this->intersects(point)) {
		const Rect& bounds = this->getRealBounds();

		booba::Event genEvent = {};
		genEvent.type = booba::EventType::CanvasMPressed;
		
		genEvent.Oleg.cedata.id = reinterpret_cast<uint64_t>(this);
		genEvent.Oleg.cedata.x  = static_cast<size_t>(point.getX() - bounds.x);
		genEvent.Oleg.cedata.y  = static_cast<size_t>(point.getY() - bounds.y);

		m_connectedTool->apply(nullptr, &genEvent);
	}
}

bool SimpleCanvas::onButtonRelease(MouseButton button, const Vec2& point)
{
	if (m_isHidden) {
		return false;
	}

	if (!m_connectedTool) {
		return false;
	}

	if (this->intersects(point)) {
		const Rect& bounds = this->getRealBounds();

		booba::Event genEvent = {};
		genEvent.type = booba::EventType::CanvasMReleased;
		
		genEvent.Oleg.cedata.id = reinterpret_cast<uint64_t>(this);
		genEvent.Oleg.cedata.x  = static_cast<size_t>(point.getX() - bounds.x);
		genEvent.Oleg.cedata.y  = static_cast<size_t>(point.getY() - bounds.y);

		m_connectedTool->apply(nullptr, &genEvent);
	}
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
