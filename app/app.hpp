#ifndef APP_HPP
#define APP_HPP

#include "window.hpp"
#include "renderer.hpp"
#include "event_manager.hpp"
#include "texture_manager.hpp"

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
	void initGraphics();
	void destroyGraphics();
	void clearHeapWidgets();

public:
	TextureManager  textureManager  = TextureManager();
	EventManager    eventManager    = EventManager();
	Window          window          = Window();
	Renderer        renderer        = Renderer();

private:
	std::string m_name = "";

	int m_winWidth  = 0;
	int m_winHeight = 0;

	bool m_isRunning = false;
};

#endif // APP_HPP
