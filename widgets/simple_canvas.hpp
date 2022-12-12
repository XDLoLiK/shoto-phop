#ifndef SIMPLE_CANVAS_HPP
#define SIMPLE_CANVAS_HPP

#include "widget.hpp"

class SimpleCanvas : public Widget
{
public:
	SimpleCanvas(booba::Tool* connectedTool = nullptr, const Rect& bounds = {0, 0, 0, 0}, Widget* parent = nullptr);
	~SimpleCanvas();

	SimpleCanvas& operator=(SimpleCanvas& other) = delete;
	SimpleCanvas(SimpleCanvas& other)            = delete;

	void setPixel(uint32_t x, uint32_t y, uint32_t color);
	void blit(Surface* surface, const Rect& bounds);

	virtual void draw()                        override;
	virtual bool intersects(const Vec2& point) override;

	virtual bool onMouseMove(const Vec2& point, const Vec2& motion)     override;
	virtual bool onButtonClick  (MouseButton button, const Vec2& point) override;
	virtual bool onButtonRelease(MouseButton button, const Vec2& point) override;

	virtual bool onKeyPress  (Key key) override;
	virtual bool onKeyRelease(Key key) override;
	virtual bool onTick(Time time)     override;

private:
	booba::Tool* m_connectedTool = nullptr;
	Surface m_drawingSurface = Surface();
};

#endif // SIMPLE_CANVAS_HPP
