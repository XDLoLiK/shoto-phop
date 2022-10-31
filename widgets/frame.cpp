#include "frame.hpp"
#include "app.hpp"


extern App* __theApp__;


Frame::Frame(Widget* parent):
	ContainerWidget(parent)
{

}

Frame::~Frame()
{

}

void Frame::draw()
{
	if (m_isHidden)
		return;

	Renderer* renderer = &__theApp__->renderer;
	renderer->copyTexture(this->getTexture(), m_bounds);
}

bool Frame::intersects(const Vec2& point)
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

void Frame::onMouseMove(const Vec2& point, const Vec2& motion)
{
	m_childrenManager.callOnMouseMove(point, motion);
}

void Frame::onButtonClick(MouseButton button, const Vec2& point)
{
	m_childrenManager.callOnButtonClick(button, point);
}

void Frame::onButtonRelease(MouseButton button, const Vec2& point)
{
	m_childrenManager.callOnButtonRelease(button, point);
}

void Frame::onKeyPress(Key key)
{
	m_childrenManager.callOnKeyPress(key);
}

void Frame::onKeyRelease(Key key)
{
	m_childrenManager.callOnKeyRelease(key);
}

void Frame::onTick(Time time)
{
	if (m_isHidden)
		return;

	this->draw();
	m_childrenManager.callOnTick(time);
}
