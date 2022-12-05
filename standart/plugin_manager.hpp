#ifndef PLUGIN_MANAGER_HPP
#define PLUGIN_MANAGER_HPP

#include <filesystem>
#include <vector>
#include <dlfcn.h>

#include "plugin.hpp"
#include "simple_canvas.hpp"
#include "simple_slider.hpp"
#include "simple_button.hpp"
#include "label.hpp"

class Canvas;

class PluginManager
{
private:
	PluginManager();

public:
	static PluginManager* getPluginManager();
	~PluginManager();

	void loadPlugins();
	void addTool(booba::Tool* tool);

	std::vector<booba::Tool*>& getTools();

private:
	std::vector<booba::Tool*> m_importedTools = std::vector<booba::Tool*>(0);
};

uint64_t booba::createButton(int32_t x, int32_t y, uint32_t w, uint32_t h, const char* text);
uint64_t booba::createLabel    (int32_t x, int32_t y, uint32_t w, uint32_t h, const char* text);
uint64_t booba::createScrollbar(int32_t x, int32_t y, uint32_t w, uint32_t h, int32_t maxValue, int32_t startValue);
uint64_t booba::createCanvas(int32_t x, int32_t y, int32_t w, int32_t h);
void booba::putPixel(uint64_t canvas, int32_t x, int32_t y, uint32_t color);
void booba::putSprite(uint64_t canvas, int32_t x, int32_t y, uint32_t w, uint32_t h, const char* texture);
void booba::addTool(booba::Tool* tool);
void booba::addFilter(booba::Tool* tool);

#endif // PLUGIN_MANAGER_HPP
