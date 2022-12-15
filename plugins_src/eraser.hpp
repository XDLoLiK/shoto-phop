#ifndef ERASER_TOOL_HPP
#define ERASER_TOOL_HPP

#include <iostream>
#include <cmath>

#include "plugin.hpp"

class EraserTool : public booba::Tool
{
public:
	EraserTool();
	virtual ~EraserTool();

	virtual void apply(booba::Image* image, const booba::Event* event) override;
	virtual const char* getTexture() override; 
	virtual void buildSetupWidget()  override;

	void drawPoint(booba::Image* image, const std::pair<int, int>& point);
	void drawLine (booba::Image* image); /* a line from prevPoint to curPoint*/

private:
	std::pair<int, int> m_curPoint  = {};
	std::pair<int, int> m_prevPoint = {};

	uint32_t m_drawColor = 0xFFFFFFFF; /* white */
	int m_brushSize = 16; /* size in pixels */

	bool m_mouseIsPressed = false;
	uint64_t m_sizeSlider = 0;
};

#endif // ERASER_TOOL_HPP
