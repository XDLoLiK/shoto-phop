#include "simple_slider.hpp"
#include "app.hpp"

SimpleSlider::SimpleSlider(booba::Tool* connectedTool, int max, int start,
              const Rect& bounds, Widget* parent):
	Frame(bounds, parent),
	m_connectedTool(connectedTool),
	m_maxValue(max),
	m_curValue(start)
{
	int sliderWidth = m_bounds.w / 20;

	double rel = static_cast<double>(start) / static_cast<double>(max);
	int startX = static_cast<int>(rel * (m_bounds.w - sliderWidth));

	Rect sliderBounds = {startX, 0, sliderWidth, m_bounds.h};

	m_slider = new Frame(sliderBounds, this);
	m_slider->setHidden(false);

	m_slider->setBackground(Color(230, 230, 230, 255));
	m_slider->setFrameColor(Color(230, 230, 230, 255));
}

SimpleSlider::~SimpleSlider()
{

}

void SimpleSlider::draw()
{
	if (m_isHidden)
		return;

	drawFrame(m_bounds);
	drawSkin (m_bounds);
}

bool SimpleSlider::intersects(const Vec2& point)
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

bool SimpleSlider::onMouseMove(const Vec2& point, const Vec2& motion)
{
	if (m_isHidden)
		return false;
	
	bool res = m_childrenManager.callOnMouseMove(point, motion);

	if (m_sliderIsHeld) {
		int x = static_cast<int>(point.getX()) - m_bounds.x - m_offset;
		x = std::min(std::max(0, x), m_bounds.w - m_slider->getBounds().w);
		m_slider->setGeometry(x, 0);

		res &= true;
	}

	int maxX = m_bounds.w - m_slider->getBounds().w;
	double rel = static_cast<double>(m_slider->getBounds().x) / static_cast<double>(maxX);
	int val = rel * m_maxValue;

	if (m_connectedTool) {
		booba::Event genEvent = {};
		genEvent.type = booba::EventType::SliderMoved;
		genEvent.Oleg.smedata.id    = reinterpret_cast<uint64_t>(this);
		genEvent.Oleg.smedata.value = val;
		m_connectedTool->apply(nullptr, &genEvent);
	}

	return res;
}

bool SimpleSlider::onButtonClick(MouseButton button, const Vec2& point)
{
	if (m_isHidden)
		return false;

	bool res = m_childrenManager.callOnButtonClick(button, point);

	if (button == SDL_BUTTON_LEFT && m_slider->intersects(point)) {
		m_sliderIsHeld = true;
		m_offset = static_cast<int>(point.getX()) - m_slider->getBounds().x;;

		res &= true;
	}

	return res;
}

bool SimpleSlider::onButtonRelease(MouseButton button, const Vec2& point)
{
	if (m_isHidden)
		return false;

	bool res = m_childrenManager.callOnButtonRelease(button, point);

	if (button == SDL_BUTTON_LEFT) {
		m_sliderIsHeld = false;

		res &= true;
	}

	return res;
}

bool SimpleSlider::onKeyPress(Key key)
{
	if (m_isHidden)
		return false;

	return m_childrenManager.callOnKeyPress(key);
}

bool SimpleSlider::onKeyRelease(Key key)
{
	if (m_isHidden)
		return false;

	return m_childrenManager.callOnKeyRelease(key);
}

bool SimpleSlider::onTick(Time time)
{
	if (m_isHidden)
		return false;

	this->draw();
	m_childrenManager.callOnTick(time);

	return true;
}
