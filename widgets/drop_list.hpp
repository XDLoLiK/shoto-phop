#ifndef DROP_LIST_HPP
#define DROP_LIST_HPP

#include "widget.hpp"
#include "signal.hpp"
#include "label.hpp"
#include "button.hpp"

#include "modifiers/framable.hpp"
#include "modifiers/skinnable.hpp"

class DropList : public ContainerWidget, public Framable, public Skinnable
{
public:
	DropList(const std::string& text = "", int size = 0, Widget* parent = nullptr);
	DropList(const std::string& text, const Rect& bounds = {0, 0, 0, 0}, Widget* parent = nullptr);
	~DropList();

	DropList& operator=(DropList&) = delete;
	DropList(DropList&)            = delete;

	bool intersectsChildren(const Vec2& point);
	void addEntry(Button* entry);

public:
	virtual void addChild   (Widget* child) override;
	virtual void removeChild(Widget* child) override;

	virtual void setGeometry(const Rect& bounds)                   override;
	virtual void setGeometry(int x, int y, int w = -1, int h = -1) override;

	virtual void draw()                        override;
	virtual bool intersects(const Vec2& point) override;

	virtual bool onMouseMove(const Vec2& point, const Vec2& motion)     override;
	virtual bool onButtonClick  (MouseButton button, const Vec2& point) override;
	virtual bool onButtonRelease(MouseButton button, const Vec2& point) override;

	virtual bool onKeyPress  (Key key) override;
	virtual bool onKeyRelease(Key key) override;
	virtual bool onTick(Time time)     override;

protected:
	Label* m_label = nullptr;
};

#endif // DROP_LIST_HPP
