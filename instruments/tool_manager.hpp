#ifndef TOOL_MANAGER_HPP
#define TOOL_MANAGER_HPP

#include "instrument.hpp"
#include "texture.hpp"
#include "plugin.hpp"

class ToolManager
{
private:
	ToolManager();

public:
	static ToolManager* getToolManager();
	~ToolManager();

	ToolManager& operator=(ToolManager&) = delete;
	ToolManager(ToolManager&)            = delete;

	void chooseTool(booba::Tool* tool);

	void operator+=(booba::Tool* tool);
	void operator-=(booba::Tool* tool);

	bool reactToMouseMove    (Surface& surf, const Vec2& point,  const Vec2& motion);
	bool reactToButtonClick  (Surface& surf, MouseButton button, const Vec2& point);
	bool reactToButtonRelease(Surface& surf, MouseButton button, const Vec2& point);

	bool reactToKeyPress  (Surface& surf, Key key);
	bool reactToKeyRelease(Surface& surf, Key key);
	bool reactToTick      (Surface& surf, Time time);

private:
	std::vector<booba::Tool*> m_tools = {};
	booba::Tool* m_currentTool = nullptr;
};

#endif // TOOL_MANAGER_HPP
