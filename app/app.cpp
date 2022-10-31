#include "app.hpp"
#include "widget.hpp"


extern std::vector<Widget*> __heapWidgets__;
extern std::vector<Widget*> __heapWidgetArrays__;

App* __theApp__ = nullptr;


App::App(const std::string& name, int width, int height):
	m_name(name),
	m_winWidth(width),
	m_winHeight(height)
{
	if (__theApp__ != nullptr)
		return;

	__theApp__ = this;

	this->initGraphics();

	window.setName(m_name);
	window.setGeometry(m_winWidth, m_winHeight);
	window.open();

	renderer.setRenderWindow(&window);
	textureManager.loadDeafultTextures();
}

App::~App()
{
	this->close();
	this->destroyGraphics();
	this->clearHeapWidgets();

	__theApp__ = nullptr;
}

void App::close()
{
	window.close();
	renderer.destroy();

	m_name = "";
	m_isRunning = false;
}

int App::run()
{
	m_isRunning = true;
	const Time frameDelay = 4; /* ~ 240fps */

	while (m_isRunning) {
		Time frameStart = this->getTime();

		renderer.clear();

		int res = eventManager.getEvent();
		if (res)  eventManager.processEvent();
		eventManager.callOnTick(this->getTime());

		renderer.present();

		Time frameTime = this->getTime() - frameStart;

		if (frameDelay > frameTime)
			this->delay(frameDelay - frameTime);	
	}

	return 0;
}

Time App::getTime()
{
	return SDL_GetTicks();
}

void App::delay(Time time)
{
	SDL_Delay(time);
}

void App::initGraphics()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		std::cout << SDL_GetError() << std::endl;

	int flags     = IMG_INIT_JPG | IMG_INIT_PNG;
	int initFlags = IMG_Init(flags);

	if ((initFlags & flags) != flags)
		std::cout << IMG_GetError() << std::endl;
}

void App::destroyGraphics()
{
	IMG_Quit();
	SDL_Quit();
}

void App::clearHeapWidgets()
{
	while (!__heapWidgets__.empty())
		delete __heapWidgets__.at(0);

	__heapWidgets__.clear();
	__heapWidgets__.shrink_to_fit();

	while (!__heapWidgetArrays__.empty())
		delete [] __heapWidgetArrays__.at(0);

	__heapWidgetArrays__.clear();
	__heapWidgetArrays__.shrink_to_fit();
}
