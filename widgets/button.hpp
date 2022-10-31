#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "widget.hpp"

class Button : public Widget
{
public:
	Button(const std::string& text = "", Widget* parent = nullptr);
	virtual ~Button();

	virtual void draw()                        override;
	virtual bool intersects(const Vec2& point) override;

	virtual void addChild   (Widget* child)    override;
	virtual void removeChild(Widget* child)    override;

	virtual size_t getChildCount()             override;
	virtual Widget* getChild(size_t pos)       override;
	virtual Widget* getParent()                override;

	virtual void onMouseMove(const Vec2& point, const Vec2& motion)     override;
	virtual void onButtonClick  (MouseButton button, const Vec2& point) override;
	virtual void onButtonRelease(MouseButton button, const Vec2& point) override;

	virtual void onKeyPress  (Key key) override;
	virtual void onKeyRelease(Key key) override;
	virtual void onTick(Time time)     override;

private:
	std::string m_name = "";
};

#endif // BUTTON_HPP
