#ifndef SIMPLE_BUTTON_HPP
#define SIMPLE_BUTTON_HPP

#include "widget.hpp"
#include "label.hpp"

#include "modifiers/skinnable.hpp"
#include "modifiers/framable.hpp"

class SimpleButton : public Widget, public Skinnable, public Framable
{
public:
	SimpleButton(booba::Tool* connectedTool = nullptr, const std::string& text = "",
		         const Rect& bounds = {0, 0, 0, 0}, Widget* parent = nullptr);
	~SimpleButton();

	SimpleButton& operator=(SimpleButton& other) = delete;
	SimpleButton(SimpleButton& other)            = delete;

	virtual void draw()                        override;
	virtual bool intersects(const Vec2& point) override;

	virtual bool onMouseMove(const Vec2& point, const Vec2& motion)     override;
	virtual bool onButtonClick  (MouseButton button, const Vec2& point) override;
	virtual bool onButtonRelease(MouseButton button, const Vec2& point) override;

	virtual bool onKeyPress  (Key key) override;
	virtual bool onKeyRelease(Key key) override;
	virtual bool onTick(Time time)     override;

private:
	Label* m_label = nullptr;
	booba::Tool* m_connectedTool = nullptr;
};

#endif // SIMPLE_BUTTON_HPP
