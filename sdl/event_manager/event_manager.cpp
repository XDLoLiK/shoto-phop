#include "app.hpp"
#include "widget.hpp"
#include "event_manager.hpp"


extern App*          __theApp__;
extern EventManager* __theEventManager__;


ChildrenManager::ChildrenManager()
{

}

ChildrenManager::~ChildrenManager()
{

}

bool ChildrenManager::callOnMouseMove(const Vec2& point, const Vec2& motion)
{
	bool ret = false;

	for (auto wid : m_widgets)
		ret &= wid->onMouseMove(point, motion);

	return ret;
}

bool ChildrenManager::callOnButtonClick(MouseButton button, const Vec2& coords)
{
	bool ret = false;

	for (auto wid : m_widgets)
		ret &= wid->onButtonClick(button, coords);

	return ret;
}

bool ChildrenManager::callOnButtonRelease(MouseButton button, const Vec2& coords)
{
	bool ret = false;

	for (auto wid : m_widgets)
		ret &= wid->onButtonRelease(button, coords);

	return ret;
}

bool ChildrenManager::callOnKeyPress(Key key)
{
	bool ret = false;

	for (auto wid : m_widgets)
		ret &= wid->onKeyPress(key);

	return ret;
}

bool ChildrenManager::callOnKeyRelease(Key key)
{
	bool ret = false;

	for (auto wid : m_widgets)
		ret &= wid->onKeyRelease(key);

	return ret;
}

bool ChildrenManager::callOnTick(Time time)
{
	bool ret = false;
	
	for (auto wid : m_widgets)
		ret &= wid->onTick(time);
 	
	return ret;
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

EventManager::EventManager(EventManager* prev):
	m_prevManager(prev)
{
	__theEventManager__ = this;
}

EventManager::~EventManager()
{
	__theEventManager__ = m_prevManager;
	m_prevManager = nullptr;
}

int EventManager::getEvent()
{
	return m_event.poll();
}

bool EventManager::callOnTick(Time time)
{
	bool ret = false;
	
	if (m_prevManager) {
		ret &= m_prevManager->callOnTick(time);
	}

	for (auto wid : m_widgets)
		ret &= wid->onTick(time);

	return ret;
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
			this->callOnKeyPress(key);
			break;
		}

		case SDL_KEYUP: {
			Key key = realEvent->key.keysym.sym;
			this->callOnKeyRelease(key);
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
