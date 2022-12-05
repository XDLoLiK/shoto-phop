#ifndef COLOR_CHOOSER_HPP
#define COLOR_CHOOSER_HPP

#include <algorithm>

#include "widget.hpp"

#include "modifiers/framable.hpp"

class ColorPicker : public Widget, public Framable
{
public:
	ColorPicker(const Rect& bounds = {0, 0, 0, 0}, Widget* parent = nullptr);
	~ColorPicker();

	Color getColor();
	void fillWithColors();
	void fillWithTones();

	virtual void draw()                        override;
	virtual bool intersects(const Vec2& point) override;

	virtual bool onMouseMove(const Vec2& point, const Vec2& motion)     override;
	virtual bool onButtonClick  (MouseButton button, const Vec2& point) override;
	virtual bool onButtonRelease(MouseButton button, const Vec2& point) override;

	virtual bool onKeyPress  (Key key) override;
	virtual bool onKeyRelease(Key key) override;
	virtual bool onTick(Time time)     override;

private:
	Surface m_colorPickerTone  = Surface();
	Surface m_colorPickerColor = Surface();

	int m_h = 0;
	int m_s = 0;
	int m_v = 0;

	Color m_color = black;
};

bool intersectsBounds(const Vec2& point, const Rect& bounds);
Color fromHSVtoRGBA(int h, int s, int v);

#endif // COLOR_CHOOSER_HPP
