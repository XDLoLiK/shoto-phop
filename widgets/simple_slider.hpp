#ifndef SIMPLE_SLIDER_HPP
#define SIMPLE_SLIDER_HPP

#include "frame.hpp"

class SimpleSlider : public Frame
{
public:
	SimpleSlider(booba::Tool* connectedTool = nullptr, int max = 0, int start = 0, 
		         const Rect& bounds = {0, 0, 0, 0}, Widget* parent = nullptr);
	~SimpleSlider();

	virtual void draw()                        override;
	virtual bool intersects(const Vec2& point) override;

	virtual bool onMouseMove(const Vec2& point, const Vec2& motion)     override;
	virtual bool onButtonClick  (MouseButton button, const Vec2& point) override;
	virtual bool onButtonRelease(MouseButton button, const Vec2& point) override;

	virtual bool onKeyPress  (Key key) override;
	virtual bool onKeyRelease(Key key) override;
	virtual bool onTick(Time time)     override;

private:
	Frame* m_slider = nullptr;

	bool m_sliderIsHeld = false;
	int  m_offset = 0;

	booba::Tool* m_connectedTool = nullptr;

	int m_maxValue = 0;
	int m_curValue = 0;
};

#endif // SIMPLE_SLIDER_HPP
