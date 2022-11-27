#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "widget.hpp"
#include "label.hpp"
#include "signal.hpp"

#include "modifiers/framable.hpp"
#include "modifiers/skinnable.hpp"
#include "modifiers/hoverable.hpp"

class Button : public Widget, public Framable, public Skinnable, public Hoverable
{
public:
	Button(const std::string& text = "", int size = 0, Widget* parent = nullptr);
	Button(const std::string& text, const Rect& bounds = {0, 0, 0, 0}, Widget* parent = nullptr);
	virtual ~Button();

	Button& operator=(Button& other) = default;
	Button(Button& other)            = default;

	void setFrameHoverColor(const Color& color);
	void setFrameDefaultColor(const Color& color);

public:
	virtual void setGeometry(const Rect& bounds)                   override;
	virtual void setGeometry(int x, int y, int w = -1, int h = -1) override;

	virtual void draw()                        override;
	virtual bool intersects(const Vec2& point) override;

public:
	virtual bool onMouseMove(const Vec2& point, const Vec2& motion)     override;
	virtual bool onButtonClick  (MouseButton button, const Vec2& point) override;
	virtual bool onButtonRelease(MouseButton button, const Vec2& point) override;

	virtual bool onKeyPress  (Key key) override;
	virtual bool onKeyRelease(Key key) override;
	virtual bool onTick(Time time)     override;

public:
	Signal<> buttonClick = {};

private:
	Label* m_label = nullptr;

	Color m_frameHoverColor   = Color(185, 130, 183, 255);
	Color m_frameDefaultColor = Color(231, 178, 212, 255);
};

#endif // BUTTON_HPP
