#ifndef FRAME_HPP
#define FRAME_HPP

#include "widget.hpp"

class Frame : public ContainerWidget
{
public:
	Frame(Widget* parent = nullptr);
	~Frame();

	virtual void draw()                        override;
	virtual bool intersects(const Vec2& point) override;

	virtual void onMouseMove(const Vec2& point, const Vec2& motion)     override;
	virtual void onButtonClick  (MouseButton button, const Vec2& point) override;
	virtual void onButtonRelease(MouseButton button, const Vec2& point) override;

	virtual void onKeyPress  (Key key) override;
	virtual void onKeyRelease(Key key) override;
	virtual void onTick(Time time)     override;
};

#endif // FRAME_HPP
