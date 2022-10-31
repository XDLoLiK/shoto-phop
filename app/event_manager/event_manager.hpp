#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP

#include <vector>
#include <cassert>

#include "event.hpp"
#include "gvec.hpp"

class Widget;

class ChildrenManager
{
public:
	ChildrenManager();
	~ChildrenManager();

	void operator+=(Widget* widget);
	void operator-=(Widget* widget);

	void callOnMouseMove(const Vec2& point, const Vec2& motion);
	void callOnButtonClick  (MouseButton button, const Vec2& coords);
	void callOnButtonRelease(MouseButton button, const Vec2& coords);

	void callOnKeyPress (Key key);
	void callOnKeyRelease(Key key);
	void callOnTick(Time time);

protected:
	std::vector<Widget*> m_widgets = {};
};

class EventManager : public ChildrenManager
{
public:
	EventManager();
	~EventManager();

	int getEvent();
	void processEvent();

private:
	Event m_event = Event();
};

#endif // EVENT_MANAGER_HPP
