#include "simple_button.hpp"
#include "app.hpp"

SimpleButton::SimpleButton(booba::Tool* connectedTool, const std::string& text, 
	                       const Rect& bounds, Widget* parent):
	Widget(bounds, parent),
	m_connectedTool(connectedTool)
{
	m_label = new Label(text, m_bounds.h, black, DEFAULT_FONT, this);

	m_bounds.w = std::max(m_label->getBounds().w, m_bounds.w);
	m_bounds.h = std::max(m_label->getBounds().h, m_bounds.h);

	m_label->setGeometry((m_bounds.w - m_label->getBounds().w) / 2, 0);

	this->setBackground(Color(120, 120, 120, 255));
	this->setFrameColor(Color(120, 120, 120, 255));
}

SimpleButton::~SimpleButton()
{
	delete m_label;
	m_label = nullptr;
}

void SimpleButton::draw()
{
	if (m_isHidden)
		return;

	drawSkin (this->getRealBounds());
	drawFrame(this->getRealBounds());

	m_label->draw();
}

bool SimpleButton::intersects(const Vec2& point)
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

bool SimpleButton::onMouseMove(const Vec2& point, const Vec2& motion)
{
	if (m_isHidden) {
		return false;
	}

	if (!this->intersects(point)) {
		this->setBackground(Color(120, 120, 120, 255));
		this->setFrameColor(Color(120, 120, 120, 255));
		return false;
	}

	this->setBackground(Color(100, 100, 100, 255));
	this->setFrameColor(Color(100, 100, 100, 255));
	return true;
}

bool SimpleButton::onButtonClick(MouseButton button, const Vec2& point)
{
	if (m_isHidden) {
		return false;
	}
}

bool SimpleButton::onButtonRelease(MouseButton button, const Vec2& point)
{
	if (m_isHidden) {
		return false;
	}

	if (!m_connectedTool) {
		return false;
	}

	if (this->intersects(point)) {
		booba::Event genEvent = {};
		genEvent.type = booba::EventType::ButtonClicked;
		genEvent.Oleg.bcedata.id = reinterpret_cast<uint64_t>(this);

		m_connectedTool->apply(nullptr, &genEvent);
	}
}

bool SimpleButton::onKeyPress(Key key)
{
	if (m_isHidden) {
		return false;
	}
}

bool SimpleButton::onKeyRelease(Key key)
{
	if (m_isHidden) {
		return false;
	}
}

bool SimpleButton::onTick(Time time)
{
	if (m_isHidden) {
		return false;
	}

	this->draw();
	return true;
}
