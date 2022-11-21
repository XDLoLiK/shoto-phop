#ifndef BRUSH_HPP
#define BRUSH_HPP

#include "color.hpp"
#include "instrument.hpp"

class Brush : public Instrument
{
public:
	Brush(const std::string& icon = "", int x = 0, int y = 0);
	~Brush();

	virtual bool apply     (Surface* surface, booba::Event* event) override;
	virtual bool mouseLeave(Surface* surface, booba::Event* event) override;

	void drawPoint(Surface* surface, const std::pair<int, int>& point);
	void drawLine (Surface* surface); /* a line from prevPoint to curPoint*/

private:
	std::pair<int, int> m_curPoint  = {};
	std::pair<int, int> m_prevPoint = {};

	Color m_drawColor = black;
	int m_brushSize   = 4; /* size in pixels */

	bool m_mouseIsPressed = false;
};

#endif // BRUSH_HPP
