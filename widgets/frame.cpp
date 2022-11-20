#include "frame.hpp"
#include "app.hpp"


extern App* __theApp__;


Frame::Frame(Widget* parent):
	ContainerWidget(parent)
{
	this->setBackground(backgroundGrey);
}

Frame::Frame(const Rect& bounds, Widget* parent):
	ContainerWidget(bounds, parent)
{
	this->setBackground(backgroundGrey);
}

Frame::~Frame()
{

}

void Frame::draw()
{
	if (m_isHidden)
		return;

	drawFrame(m_bounds);
	drawSkin (m_bounds);

	m_childrenManager.callOnTick(__theApp__->getTime());
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

bool Frame::onMouseMove(const Vec2& point, const Vec2& motion)
{
	if (m_isHidden)
		return false;
	
	return m_childrenManager.callOnMouseMove(point, motion);
}

bool Frame::onButtonClick(MouseButton button, const Vec2& point)
{
	if (m_isHidden)
		return false;

	return m_childrenManager.callOnButtonClick(button, point);
}

bool Frame::onButtonRelease(MouseButton button, const Vec2& point)
{
	if (m_isHidden)
		return false;

	return m_childrenManager.callOnButtonRelease(button, point);
}

bool Frame::onKeyPress(Key key)
{
	if (m_isHidden)
		return false;

	return m_childrenManager.callOnKeyPress(key);
}

bool Frame::onKeyRelease(Key key)
{
	if (m_isHidden)
		return false;

	return m_childrenManager.callOnKeyRelease(key);
}

bool Frame::onTick(Time time)
{
	if (m_isHidden)
		return false;

	this->draw();
	m_childrenManager.callOnTick(time);

	return true;
}
