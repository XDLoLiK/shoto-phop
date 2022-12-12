#include "plugin_manager.hpp"

PluginManager::PluginManager()
{
	m_pluginCanvas = new DynamicWindow();
}

PluginManager* PluginManager::getPluginManager()
{
	static PluginManager instance{};
	return &instance;
}

PluginManager::~PluginManager()
{

}

booba::Tool* PluginManager::getCurTool()
{
	return m_curTool;
}

DynamicWindow* PluginManager::getCanvas()
{
	return m_pluginCanvas;
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

const std::vector<booba::Tool*>& PluginManager::getTools()
{
	return m_importedTools;
}

const std::vector<Widget*>* PluginManager::getToolWidgets(booba::Tool* tool)
{
	auto found = m_setupWidgets.find(tool);
	if (found == m_setupWidgets.end()) {
		return nullptr;
	}

	return &found->second;
}

const std::pair<size_t, size_t>* PluginManager::getToolSize(booba::Tool* tool)
{
	auto found = m_sizes.find(tool);
	if (found == m_sizes.end()) {
		return nullptr;
	}

	return &found->second;
}

void PluginManager::addTool(booba::Tool* tool)
{
	m_curTool = tool;
	m_importedTools.push_back(tool);
	m_setupWidgets.insert({tool, std::vector<Widget*>(0)});
	tool->buildSetupWidget();
}

void PluginManager::addWidget(Widget* widget)
{
	m_setupWidgets.find(PluginManager::getPluginManager()->getCurTool())->second.push_back(widget);
}

void PluginManager::addSizes(const std::pair<size_t, size_t>& sizes)
{
	m_sizes.insert({PluginManager::getPluginManager()->getCurTool(), sizes});
}

bool booba::setToolBarSize(size_t w, size_t h)
{
	PluginManager::getPluginManager()->addSizes({w, h});
}

void booba::addTool(booba::Tool* tool)
{
	PluginManager::getPluginManager()->addTool(tool);
}

void booba::addFilter(booba::Tool* tool)
{
	PluginManager::getPluginManager()->addTool(tool);
}

uint64_t booba::createButton(size_t x, size_t y, size_t w, size_t h, const char* text)
{
	Rect bounds = {x, y, w, h};
	SimpleButton* newButton = new SimpleButton(PluginManager::getPluginManager()->getCurTool(), std::string(text), bounds);
	newButton->setParent(PluginManager::getPluginManager()->getCanvas());
	PluginManager::getPluginManager()->getCanvas()->addChild(newButton);
	PluginManager::getPluginManager()->addWidget(newButton);

	return reinterpret_cast<uint64_t>(newButton);
}

uint64_t booba::createLabel(size_t x, size_t y, size_t w, size_t h, const char* text)
{
	Label* newLabel = new Label(std::string(text), h);
	newLabel->setParent(PluginManager::getPluginManager()->getCanvas());
	PluginManager::getPluginManager()->getCanvas()->addChild(newLabel);
	Rect bounds = {x, y, w, h};
	newLabel->setGeometry(bounds);
	PluginManager::getPluginManager()->addWidget(newLabel);

	return reinterpret_cast<uint64_t>(newLabel);
}

uint64_t booba::createSlider(size_t x, size_t y, size_t w, size_t h, int64_t minValue, int64_t maxValue, int64_t startValue)
{
	Rect bounds = {x, y, w, h};
	SimpleSlider* newScrollbar = new SimpleSlider(PluginManager::getPluginManager()->getCurTool(), maxValue, startValue, bounds);
	newScrollbar->setParent(PluginManager::getPluginManager()->getCanvas());
	PluginManager::getPluginManager()->getCanvas()->addChild(newScrollbar);
	PluginManager::getPluginManager()->addWidget(newScrollbar);

	return reinterpret_cast<uint64_t>(newScrollbar);
}

uint64_t booba::createCanvas(size_t x, size_t y, size_t w, size_t h)
{
	Rect bounds = {x, y, w, h};
	SimpleCanvas* newCanvas = new SimpleCanvas(PluginManager::getPluginManager()->getCurTool(), bounds);
	newCanvas->setParent(PluginManager::getPluginManager()->getCanvas());
	PluginManager::getPluginManager()->getCanvas()->addChild(newCanvas);
	PluginManager::getPluginManager()->addWidget(newCanvas);

	return reinterpret_cast<uint64_t>(newCanvas);
}

void booba::putPixel(uint64_t canvas, size_t x, size_t y, uint32_t color)
{
	SimpleCanvas* canvasPtr = reinterpret_cast<SimpleCanvas*>(canvas);
	canvasPtr->setPixel(x, y, color);
}

void booba::putSprite(uint64_t canvas, size_t x, size_t y, size_t w, size_t h, const char* texture)
{
	SimpleCanvas* canvasPtr = reinterpret_cast<SimpleCanvas*>(canvas);

	Rect bounds = {x, y, w, h};
	Surface* blitSurface = new Surface(std::string(texture));

	canvasPtr->blit(blitSurface, bounds);
}
