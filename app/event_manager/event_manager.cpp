#include "app.hpp"
#include "widget.hpp"
#include "event_manager.hpp"


extern App* __theApp__;


ChildrenManager::ChildrenManager()
{

}

ChildrenManager::~ChildrenManager()
{

}

void ChildrenManager::callOnMouseMove(const Vec2& point, const Vec2& motion)
{
	for (auto wid : m_widgets)
		wid->onMouseMove(point, motion);
}

void ChildrenManager::callOnButtonClick(MouseButton button, const Vec2& coords)
{
	for (auto wid : m_widgets)
		wid->onButtonClick(button, coords);
}

void ChildrenManager::callOnButtonRelease(MouseButton button, const Vec2& coords)
{
	for (auto wid : m_widgets)
		wid->onButtonRelease(button, coords);
}

void ChildrenManager::callOnKeyPress(Key key)
{
	for (auto wid : m_widgets)
		wid->onKeyPress(key);
}

void ChildrenManager::callOnKeyRelease(Key key)
{
	for (auto wid : m_widgets)
		wid->onKeyRelease(key);
}

void ChildrenManager::callOnTick(Time time)
{
	for (auto wid : m_widgets)
		wid->onTick(time);
}

void ChildrenManager::operator+=(Widget* widget)
{
	assert(widget);
	m_widgets.push_back(widget);
}

void ChildrenManager::operator-=(Widget* widget)
{
	auto start = std::remove(m_widgets.begin(), m_widgets.end(), widget);
	auto end   = m_widgets.end();

	m_widgets.erase(start, end);
}

EventManager::EventManager()
{

}

EventManager::~EventManager()
{

}

int EventManager::getEvent()
{
	return m_event.poll();
}

void EventManager::processEvent()
{
	const SDL_Event* realEvent = m_event.getRealEvent();

	switch (realEvent->type) {
		case SDL_QUIT: {
			__theApp__->close();
			break;
		}

		case SDL_KEYDOWN: {
			Key key = realEvent->key.keysym.sym;
			this->callOnKeyRelease(key);
			break;
		}

		case SDL_KEYUP: {
			Key key = realEvent->key.keysym.sym;
			this->callOnKeyPress(key);
			break;
		}

		case SDL_MOUSEMOTION: {
			Vec2 coords(realEvent->button.x, realEvent->button.y);
			Vec2 motion(realEvent->motion.xrel, realEvent->motion.yrel);
			this->callOnMouseMove(coords, motion);
			break;
		}

		case SDL_MOUSEBUTTONDOWN: {
			Vec2 coords(realEvent->button.x, realEvent->button.y);
			MouseButton button = realEvent->button.button;
			this->callOnButtonClick(button, coords);
			break;
		}

		case SDL_MOUSEBUTTONUP: {
			Vec2 coords(realEvent->button.x, realEvent->button.y);
			MouseButton button = realEvent->button.button;
			this->callOnButtonRelease(button, coords);
			break;
		}

		default: {
			break;
		}
	}
}
