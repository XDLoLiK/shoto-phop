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
	virtual ~ChildrenManager();

	void operator+=(Widget* widget);
	void operator-=(Widget* widget);

	bool callOnMouseMove(const Vec2& point, const Vec2& motion);
	bool callOnButtonClick  (MouseButton button, const Vec2& coords);
	bool callOnButtonRelease(MouseButton button, const Vec2& coords);

	bool callOnKeyPress(Key key);
	bool callOnKeyRelease(Key key);
	virtual bool callOnTick(Time time);

protected:
	std::vector<Widget*> m_widgets = {};
};

class EventManager : public ChildrenManager
{
public:
	EventManager(EventManager* prev = nullptr);
	~EventManager();

	EventManager& operator=(EventManager& other) = delete;
	EventManager(EventManager& other)            = delete;

	int getEvent();
	void processEvent();

	virtual bool callOnTick(Time time) override;

private:
	Event m_event = Event();
	EventManager* m_prevManager = nullptr;
};

#endif // EVENT_MANAGER_HPP
