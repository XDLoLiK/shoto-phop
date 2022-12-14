#ifndef TOOLBAR_HPP
#define TOOLBAR_HPP

#include "widget.hpp"
#include "plugin.hpp"
#include "context_button.hpp"
#include "tool_manager.hpp"

#include "modifiers/skinnable.hpp"
#include "modifiers/framable.hpp"

#define ICON_DEFAULT_SIZE 40
#define MAX_RESIZE_VAL    20

class Toolbar : public ContainerWidget, public Skinnable, public Framable
{
public:
	Toolbar(const Rect& bounds = {0, 0, 0, 0}, Widget* parent = nullptr);
	~Toolbar();

	void addTool(booba::Tool* tool);
	void addTools(const std::vector<booba::Tool*>& tools);

	void shiftIcons(int val);

	virtual void draw()                        override;
	virtual bool intersects(const Vec2& point) override;

	virtual bool onMouseMove(const Vec2& point, const Vec2& motion)     override;
	virtual bool onButtonClick  (MouseButton button, const Vec2& point) override;
	virtual bool onButtonRelease(MouseButton button, const Vec2& point) override;

	virtual bool onKeyPress  (Key key) override;
	virtual bool onKeyRelease(Key key) override;
	virtual bool onTick(Time time)     override;

private:
	std::vector<ContextButton<booba::Tool>*> m_selectors = {};
};

#endif // TOOLBAR_HPP
