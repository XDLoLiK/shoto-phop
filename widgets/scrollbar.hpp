#ifndef SCROLLBAR_HPP
#define SCROLLBAR_HPP

#include "frame.hpp"

class Scrollbar : public Frame
{
public:
	Scrollbar(Widget* parent = nullptr);
	Scrollbar(const Rect& bounds, Widget* parent = nullptr);
	virtual ~Scrollbar();

	Scrollbar& operator=(Scrollbar& other) = delete;
	Scrollbar(Scrollbar& other)            = delete;

	virtual float getValue() = 0;

	virtual void draw()                        override;
	virtual bool intersects(const Vec2& point) override;

	virtual bool onKeyPress  (Key key)   override;
	virtual bool onKeyRelease(Key key)   override;
	virtual bool onTick      (Time time) override;

protected:
	Frame* m_slider = nullptr;

	bool m_sliderIsHeld = false;
	int  m_offset = 0;
};

class HScrollbar : public Scrollbar
{
public:
	HScrollbar(Widget* parent = nullptr);
	HScrollbar(const Rect& bounds, Widget* parent = nullptr);
	~HScrollbar();

	virtual float getValue() override;

	virtual bool onMouseMove    (const Vec2& point,  const Vec2& motion) override;
	virtual bool onButtonClick  (MouseButton button, const Vec2& point)  override;
	virtual bool onButtonRelease(MouseButton button, const Vec2& point)  override;
};

class VScrollbar : public Scrollbar
{
public:
	VScrollbar(Widget* parent = nullptr);
	VScrollbar(const Rect& bounds, Widget* parent = nullptr);
	~VScrollbar();

	virtual float getValue() override;

	virtual bool onMouseMove    (const Vec2& point,  const Vec2& motion) override;
	virtual bool onButtonClick  (MouseButton button, const Vec2& point)  override;
	virtual bool onButtonRelease(MouseButton button, const Vec2& point)  override;
};

#endif // SCROLLBAR_HPP
