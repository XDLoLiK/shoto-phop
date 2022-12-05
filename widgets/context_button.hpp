#ifndef CONTEXT_BUTTON_HPP
#define CONTEXT_BUTTON_HPP

#include "widget.hpp"
#include "label.hpp"
#include "signal.hpp"

#include "modifiers/framable.hpp"
#include "modifiers/skinnable.hpp"
#include "modifiers/hoverable.hpp"

template <class Context>
class ContextButton : public Widget, public Framable, public Skinnable, public Hoverable
{
public:
	ContextButton(const std::string& text = "", int size = 0, Widget* parent = nullptr):
		Widget(parent)
	{
		m_label = new Label(text, size, black);

		m_bounds.w = std::max(m_label->getBounds().w, m_bounds.w);
		m_bounds.h = std::max(m_label->getBounds().h, m_bounds.h);

		this->setDefaultTexture(Color(231, 178, 212, 255));
		this->setHoverTexture(Color(185, 130, 183, 255));
	}

	ContextButton(const std::string& text, const Rect& bounds = {0, 0, 0, 0}, Widget* parent = nullptr):
		Widget(bounds, parent)
	{
		m_label = new Label(text, m_bounds.h, black);

		m_bounds.w = std::max(m_label->getBounds().w, m_bounds.w);
		m_bounds.h = std::max(m_label->getBounds().h, m_bounds.h);

		m_label->setGeometry(m_bounds.x + (m_bounds.w - m_label->getBounds().w) / 2, m_bounds.y);

		this->setDefaultTexture(Color(231, 178, 212, 255));
		this->setHoverTexture(Color(185, 130, 183, 255));
	}

	virtual ~ContextButton()
	{
		delete m_label;
		m_label = nullptr;
	}

	ContextButton& operator=(ContextButton& other) = default;
	ContextButton(ContextButton& other)            = default;

	void setContext(Context* context)
	{
		m_context = context;
	}

	void setAction(void (*action)(Context*))
	{
		m_action = action;
	}

public:
	virtual void setGeometry(const Rect& bounds) override
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

	virtual void setGeometry(int x, int y, int w = -1, int h = -1) override
	{
		w = (w == -1) ? m_bounds.w : w;
		h = (h == -1) ? m_bounds.h : h;

		this->setGeometry({x, y, w, h});
	}

	virtual void draw()
	{
		if (m_isHidden)
			return;

		drawSkin (m_bounds);
		drawFrame(m_bounds);

		m_label->draw();
	}

	virtual bool intersects(const Vec2& point)
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

public:
	virtual bool onMouseMove(const Vec2& point, const Vec2& motion) override
	{
		if (m_isHidden)
			return false;

		if (!this->intersects(point)) {
			this->setBackground(m_defaultTexture);
			this->setFrameColor(m_frameColorDefault);
			return false;
		}

		this->setBackground(m_hoverTexture);
		this->setFrameColor(m_frameColorHover);
		return true;
	}

	virtual bool onButtonClick(MouseButton button, const Vec2& point) override
	{
		if (m_isHidden)
			return false;

		return false;
	}

	virtual bool onButtonRelease(MouseButton button, const Vec2& point) override
	{
		if (m_isHidden)
			return false;

		if (this->intersects(point) && button == SDL_BUTTON_LEFT)
			(m_action)(m_context);

		return true;
	}

	virtual bool onKeyPress(Key key) override
	{
		if (m_isHidden)
			return false;

		return false;
	}

	virtual bool onKeyRelease(Key key) override
	{
		if (m_isHidden)
			return false;

		return false;
	}

	virtual bool onTick(Time time) override
	{
		if (m_isHidden)
			return false;

		this->draw();
		return true;
	}

private:
	Context* m_context = nullptr;
	void (*m_action)(Context*) = nullptr;

	Label* m_label = nullptr;
};

#endif // CONTEXT_BUTTON_HPP
