#include "scrollbar.hpp"

Scrollbar::Scrollbar(Widget* parent):
	Frame(parent)
{
	this->setBackground(Color(200, 200, 200, 255));
	this->setFrameColor(Color(200, 200, 200, 255));
}

Scrollbar::Scrollbar(const Rect& bounds, Widget* parent):
	Frame(bounds, parent)
{
	this->setBackground(Color(200, 200, 200, 255));
	this->setFrameColor(Color(200, 200, 200, 255));
}

Scrollbar::~Scrollbar()
{
	delete m_slider;
	m_slider = nullptr;
}

void Scrollbar::draw()
{
	if (m_isHidden)
		return;

	drawFrame(this->getRealBounds());
	drawSkin (this->getRealBounds());
}

bool Scrollbar::intersects(const Vec2& point)
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

bool Scrollbar::onKeyPress(Key key)
{
	if (m_isHidden)
		return false;

	return m_childrenManager.callOnKeyPress(key);
}

bool Scrollbar::onKeyRelease(Key key)
{
	if (m_isHidden)
		return false;

	return m_childrenManager.callOnKeyRelease(key);
}

bool Scrollbar::onTick(Time time)
{
	if (m_isHidden)
		return false;

	this->draw();
	m_childrenManager.callOnTick(time);

	return true;
}

HScrollbar::HScrollbar(Widget* parent):
	Scrollbar(parent)
{
	this->setBackground(Color(200, 200, 200, 255));
	this->setFrameColor(Color(200, 200, 200, 255));
}

HScrollbar::HScrollbar(const Rect& bounds, Widget* parent):
	Scrollbar(bounds, parent)
{
	int sliderWidth = m_bounds.w / 20;
	Rect sliderBounds = {0, 0, sliderWidth, m_bounds.h};

	m_slider = new Frame(sliderBounds, this);
	m_slider->setHidden(false);

	m_slider->setBackground(Color(230, 230, 230, 255));
	m_slider->setFrameColor(Color(230, 230, 230, 255));
}

HScrollbar::~HScrollbar()
{

}

float HScrollbar::getValue()
{
	float maxValue = static_cast<float>(m_bounds.w - m_slider->getBounds().w);
	float curValue = static_cast<float>(m_slider->getRealBounds().x - this->getRealBounds().x);

	return curValue / maxValue;
}

bool HScrollbar::onMouseMove(const Vec2& point, const Vec2& motion)
{
	if (m_isHidden)
		return false;
	
	bool res = m_childrenManager.callOnMouseMove(point, motion);
	const Rect& bounds = this->getRealBounds();

	if (m_sliderIsHeld) {
		int x = static_cast<int>(point.getX()) - bounds.x - m_offset;
		x = std::min(std::max(0, x), bounds.w - m_slider->getRealBounds().w);
		m_slider->setGeometry(x, 0);

		res &= true;
	}

	return res;
}

bool HScrollbar::onButtonClick(MouseButton button, const Vec2& point)
{
	if (m_isHidden)
		return false;

	bool res = m_childrenManager.callOnButtonClick(button, point);

	if (button == SDL_BUTTON_LEFT && m_slider->intersects(point)) {
		m_sliderIsHeld = true;
		m_offset = static_cast<int>(point.getX()) - m_slider->getRealBounds().x;;

		res &= true;
	}

	return res;
}

bool HScrollbar::onButtonRelease(MouseButton button, const Vec2& point)
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

VScrollbar::VScrollbar(Widget* parent):
	Scrollbar(parent)
{
	this->setBackground(Color(200, 200, 200, 255));
	this->setFrameColor(Color(200, 200, 200, 255));
}

VScrollbar::VScrollbar(const Rect& bounds, Widget* parent):
	Scrollbar(bounds, parent)
{
	int  sliderHeight = m_bounds.h / 20;
	Rect sliderBounds = {0, 0, m_bounds.w, sliderHeight};

	m_slider = new Frame(sliderBounds, this);
	m_slider->setHidden(false);

	m_slider->setBackground(Color(230, 230, 230, 255));
	m_slider->setFrameColor(Color(230, 230, 230, 255));
}

VScrollbar::~VScrollbar()
{

}

float VScrollbar::getValue()
{
	float maxValue = static_cast<float>(m_bounds.h - m_slider->getBounds().h);
	float curValue = static_cast<float>(m_slider->getRealBounds().y - this->getRealBounds().y);

	return curValue / maxValue;
}

bool VScrollbar::onMouseMove(const Vec2& point, const Vec2& motion)
{
	if (m_isHidden)
		return false;
	
	bool res = m_childrenManager.callOnMouseMove(point, motion);
	const Rect& bounds = this->getRealBounds();

	if (m_sliderIsHeld) {
		int y = static_cast<int>(point.getY()) - bounds.y - m_offset;
		y = std::min(std::max(0, y), bounds.h - m_slider->getRealBounds().h);
		m_slider->setGeometry(0, y);

		res &= true;
	}

	return res;
}

bool VScrollbar::onButtonClick(MouseButton button, const Vec2& point)
{
	if (m_isHidden)
		return false;

	bool res = m_childrenManager.callOnButtonClick(button, point);

	if (button == SDL_BUTTON_LEFT && m_slider->intersects(point)) {
		m_sliderIsHeld = true;
		m_offset = static_cast<int>(point.getY()) - m_slider->getRealBounds().y;

		res &= true;
	}

	return res;
}

bool VScrollbar::onButtonRelease(MouseButton button, const Vec2& point)
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
