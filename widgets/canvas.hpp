#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <cstring>
#include <deque>

#include "widget.hpp"
#include "instrument.hpp"
#include "tool_manager.hpp"
#include "scrollbar.hpp"

#include "modifiers/framable.hpp"

class Canvas : public ContainerWidget, public Framable
{
public:
	Canvas(const Rect& bounds = {0, 0, 0, 0}, Widget* parent = nullptr);
	virtual ~Canvas();

	Canvas& operator=(Canvas&) = delete;
	Canvas(Canvas&)            = delete;

	void addToolBox(Frame* toolBox);
	void addTool(Instrument* tool);
	void addTools(std::vector<booba::Tool*>& tools);

	void save();
	void saveAs();
	void open();

	void setFGColor(const Color& newColor);
	void setBGColor(const Color& newColor);

public:
	virtual void draw()                        override;
	virtual bool intersects(const Vec2& point) override;

	virtual bool onMouseMove(const Vec2& point, const Vec2& motion)     override;
	virtual bool onButtonClick  (MouseButton button, const Vec2& point) override;
	virtual bool onButtonRelease(MouseButton button, const Vec2& point) override;

	virtual bool onKeyPress  (Key key) override;
	virtual bool onKeyRelease(Key key) override;
	virtual bool onTick(Time time)     override;

private:
	Surface m_drawingSurface = Surface();

	ToolManager m_toolManager = ToolManager();
	Frame* m_toolBox = nullptr;
	int m_toolsInRow = 0;
	int m_toolsNow   = 0;

	size_t m_maxStates = 32;
	bool m_ctrlPressed = false;
	std::deque <Color*> m_prevStates = {};

	HScrollbar* m_horizontalBar = nullptr;
	VScrollbar* m_verticalBar   = nullptr;
	Rect m_copyBounds = {0, 0, 0, 0};

	Frame* m_cornerSquare = nullptr;

	Color m_bgColor = white;
	Color m_fgColor = black;
};

#endif // CANVAS_HPP
