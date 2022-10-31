#include "app.hpp"
#include "button.hpp"


extern App* __theApp__;


Button::Button(const std::string& text, Widget* parent):
	Widget(parent),
	m_name(text)
{

}

Button::~Button()
{

}

void Button::draw()
{
	if (m_isHidden)
		return;

	Renderer* renderer = &__theApp__->renderer;
	renderer->copyTexture(this->getTexture(), m_bounds);
}

bool Button::intersects(const Vec2& point)
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

void Button::addChild(Widget*)
{

}

void Button::removeChild(Widget*)
{

}

size_t Button::getChildCount()
{
	return 0;
}

Widget* Button::getChild(size_t)
{
	return nullptr;
}

Widget* Button::getParent()
{
	return m_parent;
}

void Button::onMouseMove(const Vec2& point, const Vec2& motion)
{

}

void Button::onButtonClick(MouseButton, const Vec2&)
{

}

void Button::onButtonRelease(MouseButton button, const Vec2& point)
{

}

void Button::onKeyPress(Key)
{

}

void Button::onKeyRelease(Key)
{

}

void Button::onTick(Time)
{
	if (m_isHidden)
		return;

	this->draw();
}
