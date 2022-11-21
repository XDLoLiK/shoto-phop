#ifndef TOOL_MANAGER_HPP
#define TOOL_MANAGER_HPP

#include "instrument.hpp"
#include "texture.hpp"

class ToolManager
{
public:
	ToolManager();
	~ToolManager();

	ToolManager& operator=(ToolManager&) = delete;
	ToolManager(ToolManager&)            = delete;

	void operator+=(Instrument* tool);
	void operator-=(Instrument* tool);

	bool reactToMouseMove    (Surface& surf, const Vec2& point,  const Vec2& motion);
	bool reactToButtonClick  (Surface& surf, MouseButton button, const Vec2& point);
	bool reactToButtonRelease(Surface& surf, MouseButton button, const Vec2& point);

	bool reactToKeyPress  (Surface& surf, Key key);
	bool reactToKeyRelease(Surface& surf, Key key);
	bool reactToTick      (Surface& surf, Time time);

	bool changeTool(MouseButton button, const Vec2& point);
	bool reactToMouseLeave(Surface& surf, const Vec2& point, const Vec2& motion);

private:
	std::vector<Instrument*> m_tools = {};
	Instrument* m_currentTool = nullptr;
};

#endif // TOOL_MANAGER_HPP
