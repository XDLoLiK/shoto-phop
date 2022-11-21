#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP

#include <vector>
#include <cassert>

#include "event.hpp"
#include "vec.hpp"

class Widget;

class ChildrenManager
{
public:
	ChildrenManager();
	~ChildrenManager();

	void operator+=(Widget* widget);
	void operator-=(Widget* widget);

	bool callOnMouseMove(const Vec2& point, const Vec2& motion);
	bool callOnButtonClick  (MouseButton button, const Vec2& coords);
	bool callOnButtonRelease(MouseButton button, const Vec2& coords);

	bool callOnKeyPress(Key key);
	bool callOnKeyRelease(Key key);
	bool callOnTick(Time time);

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
