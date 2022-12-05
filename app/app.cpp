#include "app.hpp"
#include "widget.hpp"


/* Global variable needed for plugins */
booba::ApplicationContext* booba::APPCONTEXT = nullptr;

extern std::vector<Widget*> __heapWidgets__;
extern std::vector<Widget*> __heapWidgetArrays__;

App*           __theApp__           = nullptr;
EventManager*  __theEventManager__  = nullptr;


App::App(const std::string& name, int width, int height):
	m_name(name),
	m_winWidth(width),
	m_winHeight(height)
{
	if (__theApp__ != nullptr) {
		std::cout << "You can have only one App instance" << std::endl;
		return;
	}
	__theApp__           = this;
	__theEventManager__  = &this->m_eventManager;

	this->initGraphics();

	m_window.setName(m_name);
	m_window.setGeometry(m_winWidth, m_winHeight);
	m_window.open();

	m_renderer.setRenderTarget(&m_window);

	booba::APPCONTEXT = new booba::ApplicationContext();
	booba::APPCONTEXT->fgColor = black.mapRGBA();
	booba::APPCONTEXT->bgColor = white.mapRGBA();

	SkinManager::getSkinManager()->loadDeafultSkins();
	PluginManager::getPluginManager()->loadPlugins();
}

App::~App()
{
	this->close();
	this->destroyGraphics();
	this->clearHeapWidgets();

	delete booba::APPCONTEXT;

	__theApp__ = nullptr;
}

void App::close()
{
	m_window.close();
	m_renderer.destroy();

	m_name = "";
	m_isRunning = false;
}

int App::run()
{
	EventManager* eventManager = __theEventManager__;

	m_isRunning = true;
	const Time frameDelay = 4; /* ~ 240fps */

	while (m_isRunning) {
		Time frameStart = this->getTime();

		m_renderer.clear();

		while (eventManager->getEvent()) {
			eventManager->processEvent();
			eventManager = __theEventManager__;
		}

		eventManager->callOnTick(this->getTime());
		m_renderer.present();

		Time frameTime = this->getTime() - frameStart;
		if (frameDelay > frameTime)
			this->delay(frameDelay - frameTime);	
	}

	return 0;
}

Window* App::getWindow()
{
	return &m_window;
}

Renderer* App::getRenderer()
{
	return &m_renderer;
}

Time App::getTime()
{
	return SDL_GetTicks();
}

void App::delay(Time time)
{
	SDL_Delay(time);
}

bool App::initGraphics()
{
	/* Init SDL */
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << SDL_GetError() << std::endl;
		return false;
	}

	/* Init SDL_image */
	int flags     = IMG_INIT_JPG | IMG_INIT_PNG;
	int initFlags = IMG_Init(flags);

	if ((initFlags & flags) != flags) {
		std::cout << IMG_GetError() << std::endl;
		return false;
	}

	/* Init SDL_ttf */
	TTF_Init();

	return true;
}

void App::destroyGraphics()
{
	TTF_Quit();
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

App* getApp()
{
	return __theApp__;
}

EventManager* getEventManager()
{
	return __theEventManager__;
}
