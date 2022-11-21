#ifndef ERASER_HPP
#define ERASER_HPP

#include "brush.hpp"
#include "cursor.hpp"

class Eraser : public Instrument
{
public:
	Eraser(const std::string& icon = "", int x = 0, int y = 0);
	~Eraser();

	virtual bool apply     (Surface* surface, booba::Event* event) override;
	virtual bool mouseLeave(Surface* surface, booba::Event* event) override;
	
	void drawPoint(Surface* surface, const std::pair<int, int>& point);
	void drawLine (Surface* surface); /* a line from prevPoint to curPoint*/

private:
	std::pair<int, int> m_curPoint  = {};
	std::pair<int, int> m_prevPoint = {};

	const Color m_eraseColor = white;
	int m_brushSize = 16; /* size in pixels */

	bool m_mouseIsPressed = false;
};

#endif // ERASER_HPP
