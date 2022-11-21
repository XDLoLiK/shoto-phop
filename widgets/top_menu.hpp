#ifndef TOP_MENU_HPP
#define TOP_MENU_HPP

#include "frame.hpp"

class TopMenu : public Frame
{
public:
	TopMenu(Widget* parent = nullptr);
	TopMenu(const Rect& bounds, Widget* parent = nullptr);
	~TopMenu();

	TopMenu& operator=(TopMenu&) = delete;
	TopMenu(TopMenu&)            = delete;

	virtual void addChild(Widget* child) override;
	virtual void draw()                  override;

private:
	Widget* m_latestChild = nullptr;
};

#endif // TOP_MENU_HPP
