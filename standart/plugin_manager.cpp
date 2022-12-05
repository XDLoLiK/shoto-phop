#include "plugin_manager.hpp"


booba::Tool* __currentImportTool__ = nullptr;


PluginManager::PluginManager()
{

}

PluginManager* PluginManager::getPluginManager()
{
	static PluginManager instance;
	return &instance;
}

PluginManager::~PluginManager()
{

}

void PluginManager::loadPlugins()
{
	static bool wasCalled = false;
	if (wasCalled) return;

	const std::string src = "./plugins";

	for (const auto& file : std::filesystem::directory_iterator(src)) {
		if (file.is_directory()) {
			continue;
		}

		void* soHandler = dlopen(file.path().c_str(), RTLD_LAZY);
		if (!soHandler) {
			std::cout << "Unable to open " << file.path() << " due to " << dlerror() << std::endl;
			continue;
		}

		void (*pluginInit) () = reinterpret_cast<void (*) ()>(dlsym(soHandler, "init_module"));
		if (!pluginInit) {
			std::cout << file.path() << " lacks void init_module()" << std::endl;
			continue;
		}

		pluginInit();
	}

	wasCalled = true;
}

std::vector<booba::Tool*>& PluginManager::getTools()
{
	return m_importedTools;
}

void PluginManager::addTool(booba::Tool* tool)
{
	m_importedTools.push_back(tool);
}

void booba::addTool(booba::Tool* tool)
{
	PluginManager::getPluginManager()->addTool(tool);
}

void booba::addFilter(booba::Tool* tool)
{
	PluginManager::getPluginManager()->addTool(tool);
}

uint64_t booba::createButton(int32_t x, int32_t y, uint32_t w, uint32_t h, const char* text)
{
	Rect bounds = {x, y, w, h};
	SimpleButton* newButton = new SimpleButton(__currentImportTool__, std::string(text), bounds);

	return reinterpret_cast<uint64_t>(newButton);
}

uint64_t booba::createLabel(int32_t x, int32_t y, uint32_t w, uint32_t h, const char* text)
{
	Label* newLabel = new Label(std::string(text), h);
	Rect bounds = {x, y, w, h};
	newLabel->setGeometry(bounds);

	return reinterpret_cast<uint64_t>(newLabel);
}

uint64_t booba::createScrollbar(int32_t x, int32_t y, uint32_t w, uint32_t h, int32_t maxValue, int32_t startValue)
{
	Rect bounds = {x, y, w, h};
	SimpleSlider* newScrollbar = new SimpleSlider(__currentImportTool__, maxValue, startValue, bounds);

	return reinterpret_cast<uint64_t>(newScrollbar);
}

uint64_t booba::createCanvas(int32_t x, int32_t y, int32_t w, int32_t h)
{
	Rect bounds = {x, y, w, h};
	SimpleCanvas* newCanvas = new SimpleCanvas(__currentImportTool__, bounds);

	return reinterpret_cast<uint64_t>(newCanvas);
}

void booba::putPixel(uint64_t canvas, int32_t x, int32_t y, uint32_t color)
{
	SimpleCanvas* canvasPtr = reinterpret_cast<SimpleCanvas*>(canvas);
	canvasPtr->putPixel(x, y, color);
}

void booba::putSprite(uint64_t canvas, int32_t x, int32_t y, uint32_t w, uint32_t h, const char* texture)
{
	SimpleCanvas* canvasPtr = reinterpret_cast<SimpleCanvas*>(canvas);

	Rect bounds = {x, y, w, h};
	Surface* blitSurface = new Surface(std::string(texture));

	canvasPtr->blit(blitSurface, bounds);
}
