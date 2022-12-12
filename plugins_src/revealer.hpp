#ifndef REVEALER_TOOL_HPP
#define REVEALER_TOOL_HPP

#include <iostream>
#include <cmath>

#include "plugin.hpp"

class RevealerTool : public booba::Tool
{
public:
	RevealerTool();
	virtual ~RevealerTool();

	virtual void apply(booba::Image* image, const booba::Event* event) override;
	virtual const char* getTexture() override; 
	virtual void buildSetupWidget()  override;

	void drawPoint(booba::Image* image, const std::pair<int, int>& point);
	void drawLine (booba::Image* image); /* a line from prevPoint to curPoint*/

private:
	std::pair<int, int> m_curPoint  = {};
	std::pair<int, int> m_prevPoint = {};

	uint32_t m_drawColor = 0x00000000; /* transparent */
	int m_brushSize = 16; /* size in pixels */

	bool m_mouseIsPressed = false;
};

#endif // REVEALER_TOOL_HPP
