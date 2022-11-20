#ifndef FRAME_HPP
#define FRAME_HPP

#include "widget.hpp"
#include "skinnable.hpp"
#include "framable.hpp"

class Frame : public ContainerWidget, public Skinnable, public Framable
{
public:
	Frame(Widget* parent = nullptr);
	Frame(const Rect& bounds, Widget* parent = nullptr);
	virtual ~Frame();

	virtual void draw()                        override;
	virtual bool intersects(const Vec2& point) override;

	virtual bool onMouseMove    (const Vec2& point,  const Vec2& motion) override;
	virtual bool onButtonClick  (MouseButton button, const Vec2& point)  override;
	virtual bool onButtonRelease(MouseButton button, const Vec2& point)  override;

	virtual bool onKeyPress  (Key key)   override;
	virtual bool onKeyRelease(Key key)   override;
	virtual bool onTick      (Time time) override;
};

#endif // FRAME_HPP
