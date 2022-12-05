#include "simple_button.hpp"
#include "app.hpp"

SimpleButton::SimpleButton(booba::Tool* connectedTool, const std::string& text, 
	                       const Rect& bounds, Widget* parent):
	Widget(bounds, parent),
	m_connectedTool(connectedTool)
{
	m_label = new Label(text, m_bounds.h, black);

	m_bounds.w = std::max(m_label->getBounds().w, m_bounds.w);
	m_bounds.h = std::max(m_label->getBounds().h, m_bounds.h);

	m_label->setGeometry(m_bounds.x + (m_bounds.w - m_label->getBounds().w) / 2, m_bounds.y);

	this->setBackground(Color(231, 178, 212, 255));
	this->setFrameColor(Color(231, 178, 212, 255));
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

	drawSkin (m_bounds);
	drawFrame(m_bounds);

	m_label->draw();
}

bool SimpleButton::intersects(const Vec2& point)
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

bool SimpleButton::onMouseMove(const Vec2& point, const Vec2& motion)
{
	if (m_isHidden) {
		return false;
	}

	if (!this->intersects(point)) {
		this->setBackground(Color(231, 178, 212, 255));
		this->setFrameColor(Color(231, 178, 212, 255));
		return false;
	}

	this->setBackground(Color(185, 130, 183, 255));
	this->setFrameColor(Color(185, 130, 183, 255));
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

	booba::Event genEvent = {};
	genEvent.type = booba::EventType::ButtonClicked;
	genEvent.Oleg.bcedata.id = reinterpret_cast<uint64_t>(this);

	m_connectedTool->apply(nullptr, &genEvent);
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
