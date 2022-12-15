#ifndef CONTEXT_BUTTON_HPP
#define CONTEXT_BUTTON_HPP

#include "widget.hpp"
#include "label.hpp"
#include "signal.hpp"

#include "modifiers/framable.hpp"
#include "modifiers/skinnable.hpp"
#include "modifiers/hoverable.hpp"

template <class Context>
class ContextButton : public Widget, public Framable, public Skinnable
{
public:
	ContextButton(const std::string& text = "", int size = 0, const Color& color = black, Widget* parent = nullptr):
		Widget(parent),
		m_textColor(color)
	{
		m_label = new Label(text, size, m_textColor, DEFAULT_FONT, this);

		m_bounds.w = std::max(m_label->getBounds().w, m_bounds.w);
		m_bounds.h = std::max(m_label->getBounds().h, m_bounds.h);

		this->setBackgroundDefault(Color(231, 178, 212, 255));
		this->setBackgroundHover(Color(185, 130, 183, 255));
		this->setFrameColorDefault(Color(231, 178, 212, 255));
		this->setFrameColorHover(Color(185, 130, 183, 255));
	}

	ContextButton(const std::string& text, const Rect& bounds = {0, 0, 0, 0}, const Color& color = black, Widget* parent = nullptr):
		Widget(bounds, parent),
		m_textColor(color)
	{
		m_label = new Label(text, m_bounds.h, m_textColor, DEFAULT_FONT, this);

		m_bounds.w = std::max(m_label->getBounds().w, m_bounds.w);
		m_bounds.h = std::max(m_label->getBounds().h, m_bounds.h);

		m_label->setGeometry((m_bounds.w - m_label->getBounds().w) / 2, 0);

		this->setBackgroundDefault(Color(231, 178, 212, 255));
		this->setBackgroundHover(Color(185, 130, 183, 255));
		this->setFrameColorDefault(Color(231, 178, 212, 255));
		this->setFrameColorHover(Color(185, 130, 183, 255));
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

	void setShortcut(Key key)
	{
		m_hasShortcut = true;
		m_shotrcut = key;
	}

public:
	virtual void setGeometry(const Rect& bounds) override
	{
		m_bounds = bounds;

		const std::string& oldText = m_label->getText();
		delete m_label;

		m_label = new Label(oldText, m_bounds.h, m_textColor, DEFAULT_FONT, this);

		m_bounds.w = std::max(m_label->getBounds().w, m_bounds.w);
		m_bounds.h = std::max(m_label->getBounds().h, m_bounds.h);
		
		m_label->setGeometry((m_bounds.w - m_label->getBounds().w) / 2, 0);
	}

	virtual void setGeometry(int x, int y, int w = -1, int h = -1) override
	{
		w = (w == -1) ? m_bounds.w : w;
		h = (h == -1) ? m_bounds.h : h;

		this->setGeometry({x, y, w, h});
	}

	virtual void draw() override
	{
		if (m_isHidden)
			return;

		drawSkin (this->getRealBounds(), m_isHovered);
		drawFrame(this->getRealBounds(), m_isHovered);

		m_label->draw();
	}

	virtual bool intersects(const Vec2& point) override
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

public:
	virtual bool onMouseMove(const Vec2& point, const Vec2&) override
	{
		if (m_isHidden)
			return false;

		if (!this->intersects(point)) {
			m_isHovered = false;
			return false;
		}

		m_isHovered = true;
		return true;
	}

	virtual bool onButtonClick(MouseButton, const Vec2& point) override
	{
		if (m_isHidden)
			return false;

		if (this->intersects(point)) {
			return true;
		}

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

		if (key == SDLK_LCTRL) {
			m_ctrlPresed = true;
		}

		if (m_ctrlPresed && m_hasShortcut && key == m_shotrcut) {
			(m_action)(m_context);
			return true;
		}

		return false;
	}

	virtual bool onKeyRelease(Key key) override
	{
		if (m_isHidden)
			return false;

		if (key == SDLK_LCTRL) {
			m_ctrlPresed = false;
		}

		return false;
	}

	virtual bool onTick(Time) override
	{
		if (m_isHidden)
			return false;

		this->draw();
		return true;
	}

private:
	Context* m_context = nullptr;
	void (*m_action)(Context*) = nullptr;

	bool m_ctrlPresed  = false;
	bool m_hasShortcut = false;
	Key m_shotrcut = SDLK_ESCAPE;

	Label* m_label = nullptr;
	Color m_textColor = black;
};

#endif // CONTEXT_BUTTON_HPP
