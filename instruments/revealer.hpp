#ifndef REVEALER_HPP
#define REVEALER_HPP

#include "brush.hpp"
#include "cursor.hpp"

class Revealer : public Instrument
{
public:
	Revealer(const std::string& icon = "", int x = 0, int y = 0);
	~Revealer();

	virtual bool apply     (Surface* surface, booba::Event* event) override;
	virtual bool mouseLeave(Surface* surface, booba::Event* event) override;
	
	void drawPoint(Surface* surface, const std::pair<int, int>& point);
	void drawLine (Surface* surface); /* a line from prevPoint to curPoint*/

private:
	std::pair<int, int> m_curPoint  = {};
	std::pair<int, int> m_prevPoint = {};

	const Color m_eraseColor = Color(255, 255, 255, 0);
	int m_brushSize = 40; /* size in pixels */

	bool m_mouseIsPressed = false;
};

#endif // REVEALER_HPP
