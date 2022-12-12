#ifndef BRUSH_TOOL_HPP
#define BRUSH_TOOL_HPP

#include <iostream>
#include <cmath>

#include "plugin.hpp"

class BrushTool : public booba::Tool
{
public:
	BrushTool();
	virtual ~BrushTool();

	virtual void apply(booba::Image* image, const booba::Event* event) override;
	virtual const char* getTexture() override; 
	virtual void buildSetupWidget()  override;

	void drawPoint(booba::Image* image, const std::pair<int, int>& point);
	void drawLine (booba::Image* image); /* a line from prevPoint to curPoint*/

private:
	std::pair<int, int> m_curPoint  = {};
	std::pair<int, int> m_prevPoint = {};

	uint32_t m_drawColor = 0x000000FF; /* black */
	int m_brushSize = 4; /* size in pixels */

	bool m_mouseIsPressed = false;
};

#endif // BRUSH_TOOL_HPP
