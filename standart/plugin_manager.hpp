#ifndef PLUGIN_MANAGER_HPP
#define PLUGIN_MANAGER_HPP

#include <filesystem>
#include <vector>
#include <unordered_map>
#include <dlfcn.h>

#include "plugin.hpp"
#include "simple_canvas.hpp"
#include "simple_slider.hpp"
#include "simple_button.hpp"

#include "label.hpp"
#include "dynamic_window.hpp"

class PluginManager
{
private:
	PluginManager();

public:
	static PluginManager* getPluginManager();
	~PluginManager();

	PluginManager& operator=(PluginManager& other) = delete;
	PluginManager(PluginManager& other)            = delete;

	void loadPlugins();

	void addTool  (booba::Tool* tool);
	void addWidget(Widget* widget);
	void addSizes (const std::pair<size_t, size_t>& sizes);

	const std::vector<booba::Tool*>& getTools();
	const std::vector<Widget*>* getToolWidgets  (booba::Tool* tool);
	const std::pair<size_t, size_t>* getToolSize(booba::Tool* tool);

	booba::Tool*   getCurTool();
	DynamicWindow* getCanvas ();

private:
	booba::Tool*   m_curTool      = nullptr;
	DynamicWindow* m_pluginCanvas = nullptr;

	std::vector<booba::Tool*> m_importedTools = {};
	std::unordered_map<booba::Tool*, std::vector<Widget*>> m_setupWidgets = {};
	std::unordered_map<booba::Tool*, std::pair<size_t, size_t>> m_sizes   = {};
};

#endif // PLUGIN_MANAGER_HPP
