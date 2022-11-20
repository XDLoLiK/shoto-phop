#ifndef APP_HPP
#define APP_HPP

#include "window.hpp"
#include "renderer.hpp"

#include "event_manager.hpp"
#include "skin_manager.hpp"

class App
{
public:
	App(const std::string& name = "", int width = 0, int height = 0);
	~App();

	Time getTime();
	void delay(Time time);

	void close();
	int run();

private:
	bool initGraphics();
	void destroyGraphics();
	void clearHeapWidgets();

public:
	Window*   getWindow();
	Renderer* getRenderer();

private:
	SkinManager  m_skinManager  = SkinManager();
	EventManager m_eventManager = EventManager();
	Window       m_window       = Window();
	Renderer     m_renderer     = Renderer();

private:
	std::string m_name = "";

	int m_winWidth  = 0;
	int m_winHeight = 0;

	bool m_isRunning = false;
};

App* getApp();

#endif // APP_HPP
