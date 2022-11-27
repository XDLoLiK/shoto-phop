#include "instrument.hpp"
#include "app.hpp"

Instrument::Instrument(const std::string& icon, int x, int y)
{
	m_icon = new Frame({x, y, 40, 40});
	m_icon->setFrameColor(white);
	m_icon->setBackground(icon);
	m_icon->setHidden(false);
}

Instrument::~Instrument()
{
	delete m_icon;
}

bool Instrument::mouseLeave(Surface*, booba::Event*)
{
	return false;
}

bool Instrument::isSelected(MouseButton button, const Vec2& point)
{
	if (m_icon->intersects(point) && button == SDL_BUTTON_LEFT)
		return true;

	return false;
}

void Instrument::select()
{
	m_icon->setFrameColor(black);
}

void Instrument::deselect()
{
	m_icon->setFrameColor(white);
}

void Instrument::drawIcon(Time)
{
	m_icon->draw();
}

void Instrument::drawCursor(Time)
{

}

void Instrument::setIconPos(int x, int y, int w, int h)
{
	m_icon->setGeometry(x, y, w, h);
}

void Instrument::setIconPos(const Rect& bounds)
{
	m_icon->setGeometry(bounds);
}
