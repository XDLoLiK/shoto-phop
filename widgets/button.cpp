#include "app.hpp"
#include "button.hpp"


extern App* __theApp__;


Button::Button(const std::string& text, int size, Widget* parent):
	Widget(parent)
{
	m_label = new Label(text, size, black);

	m_bounds.w = std::max(m_label->getBounds().w, m_bounds.w);
	m_bounds.h = std::max(m_label->getBounds().h, m_bounds.h);

	this->setDefaultTexture(Color(231, 178, 212, 255));
	this->setHoverTexture(Color(185, 130, 183, 255));

	this->setFrameColor(m_frameDefaultColor);
	this->setBackground(m_defaultTexture);
}

Button::Button(const std::string& text, const Rect& bounds, Widget* parent):
	Widget(bounds, parent)
{
	m_label = new Label(text, m_bounds.h, black);

	m_bounds.w = std::max(m_label->getBounds().w, m_bounds.w);
	m_bounds.h = std::max(m_label->getBounds().h, m_bounds.h);

	m_label->setGeometry(m_bounds.x + (m_bounds.w - m_label->getBounds().w) / 2, m_bounds.y);

	this->setDefaultTexture(Color(231, 178, 212, 255));
	this->setHoverTexture(Color(185, 130, 183, 255));

	this->setFrameColor(m_frameDefaultColor);
	this->setBackground(m_defaultTexture);
}

Button::~Button()
{
	delete m_label;
	m_label = nullptr;
}

void Button::setFrameHoverColor(const Color& color)
{
	m_frameHoverColor = color;
}

void Button::setFrameDefaultColor(const Color& color)
{
	m_frameDefaultColor = color;
}

void Button::setGeometry(const Rect& bounds)
{
	m_bounds = bounds;
	Widget* curWid = m_parent;

	while (curWid) {
		m_bounds.x += curWid->getBounds().x;
		m_bounds.y += curWid->getBounds().y;
		curWid = curWid->getParent();
	}

	const std::string& oldText = m_label->getText();
	delete m_label;

	m_label = new Label(oldText, m_bounds.h, black);

	m_bounds.w = std::max(m_label->getBounds().w, m_bounds.w);
	m_bounds.h = std::max(m_label->getBounds().h, m_bounds.h);
	
	m_label->setGeometry(m_bounds.x + (m_bounds.w - m_label->getBounds().w) / 2, m_bounds.y);
}

void Button::setGeometry(int x, int y, int w, int h)
{
	w = (w == -1) ? m_bounds.w : w;
	h = (h == -1) ? m_bounds.h : h;

	this->setGeometry({x, y, w, h});
}

void Button::draw()
{
	if (m_isHidden)
		return;

	drawSkin (m_bounds);
	drawFrame(m_bounds);

	m_label->draw();
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

bool Button::onMouseMove(const Vec2& point, const Vec2&)
{
	if (m_isHidden)
		return false;

	if (!this->intersects(point)) {
		this->setBackground(m_defaultTexture);
		this->setFrameColor(m_frameDefaultColor);
		return false;
	}

	this->setBackground(m_hoverTexture);
	this->setFrameColor(m_frameHoverColor);
	return true;
}

bool Button::onButtonClick(MouseButton, const Vec2&)
{
	if (m_isHidden)
		return false;

	return false;
}

bool Button::onButtonRelease(MouseButton button, const Vec2& point)
{
	if (m_isHidden)
		return false;

	if (this->intersects(point) && button == SDL_BUTTON_LEFT)
		buttonClick();

	return true;
}

bool Button::onKeyPress(Key)
{
	if (m_isHidden)
		return false;

	return false;
}

bool Button::onKeyRelease(Key)
{
	if (m_isHidden)
		return false;

	return false;
}

bool Button::onTick(Time)
{
	if (m_isHidden)
		return false;

	this->draw();
	return true;
}
