#ifndef DYNAMIC_WINDOW_HPP
#define DYNAMIC_WINDOW_HPP

#include "widget.hpp"
#include "frame.hpp"
#include "button.hpp"

#include "modifiers/framable.hpp"
#include "modifiers/skinnable.hpp"

#define MIN_WIN_WIDTH  100
#define MIN_WIN_HEIGHT 20

class DynamicWindow : public ContainerWidget, public Skinnable, public Framable
{
public:
	DynamicWindow(const Rect& bounds = {0, 0, 0, 0}, Widget* parent = nullptr);
	~DynamicWindow();

	DynamicWindow& operator=(DynamicWindow& other) = delete;
	DynamicWindow(DynamicWindow& other)            = delete;

	void shiftChildren(int xShift, int yShift);
	void setSizes(const std::pair<size_t, size_t>& sizes);

	virtual void show() override;
	// virtual void setGeometry(const Rect& bounds) override;

	virtual void draw()                        override;
	virtual bool intersects(const Vec2& point) override;

	virtual bool onMouseMove(const Vec2& point, const Vec2& motion)     override;
	virtual bool onButtonClick  (MouseButton button, const Vec2& point) override;
	virtual bool onButtonRelease(MouseButton button, const Vec2& point) override;

	virtual bool onKeyPress  (Key key) override;
	virtual bool onKeyRelease(Key key) override;
	virtual bool onTick(Time time)     override;

private:
	Frame*  m_topMenu     = nullptr;
	Button* m_closeButton = nullptr;

	bool m_btnPressed = false;
};

#endif // DYNAMIC_WINDOW_HPP
