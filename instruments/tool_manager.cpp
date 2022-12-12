#include "tool_manager.hpp"
#include "app.hpp"

ToolManager::ToolManager()
{
	m_currentTool = nullptr;
}

ToolManager* ToolManager::getToolManager()
{
	static ToolManager instance;
	return &instance;
}

void ToolManager::chooseTool(booba::Tool* tool)
{
	m_currentTool = tool;
}

booba::Tool* ToolManager::getCurTool()
{
	return m_currentTool;
}

ToolManager::~ToolManager()
{
	for (size_t i = 0; i < m_tools.size(); i++)
		delete m_tools[i];

	m_tools.clear();
	m_tools.shrink_to_fit();

	m_currentTool = nullptr;
}

bool ToolManager::reactToMouseMove(Surface& surf, const Vec2& point, const Vec2& motion)
{
	if (!m_currentTool)
		return false;

	int x = static_cast<int>(point.getX());
	int y = static_cast<int>(point.getY());

	int relX = static_cast<int>(motion.getX());
	int relY = static_cast<int>(motion.getX());

	booba::Event genEvent = {};
	genEvent.type = booba::EventType::MouseMoved;
	genEvent.Oleg.motion = {x, y, relX, relY};

	m_currentTool->apply(&surf, &genEvent);
}

bool ToolManager::reactToButtonClick(Surface& surf, MouseButton button, const Vec2& point)
{
	if (!m_currentTool)
		return false;

	booba::MouseButton btn = (button == SDL_BUTTON_LEFT) ? booba::MouseButton::Left
	                                                     : booba::MouseButton::Right;

    int x = static_cast<int>(point.getX());
    int y = static_cast<int>(point.getY());

	booba::Event genEvent = {};
	genEvent.type = booba::EventType::MousePressed;
	genEvent.Oleg.mbedata = {x, y, btn};

	m_currentTool->apply(&surf, &genEvent);
}

bool ToolManager::reactToButtonRelease(Surface& surf, MouseButton button, const Vec2& point)
{
	if (!m_currentTool)
		return false;

	booba::MouseButton btn = (button == SDL_BUTTON_LEFT) ? booba::MouseButton::Left
	                                                     : booba::MouseButton::Right;
    
    int x = static_cast<int>(point.getX());
    int y = static_cast<int>(point.getY());

	booba::Event genEvent = {};
	genEvent.type = booba::EventType::MouseReleased;
	genEvent.Oleg.mbedata = {x, y, btn};

	m_currentTool->apply(&surf, &genEvent);
}

bool ToolManager::reactToKeyPress(Surface&, Key)
{
	if (!m_currentTool)
		return false;

	return false;
}

bool ToolManager::reactToKeyRelease(Surface&, Key)
{
	if (!m_currentTool)
		return false;

	return false;
}

bool ToolManager::reactToTick(Surface&, Time time)
{
	if (!m_currentTool) 
		return false;
}

void ToolManager::operator+=(booba::Tool* tool)
{
	assert(tool);
	m_tools.push_back(tool);
}

void ToolManager::operator-=(booba::Tool* tool)
{
	auto start = std::remove(m_tools.begin(), m_tools.end(), tool);
	auto end   = m_tools.end();

	m_tools.erase(start, end);
}