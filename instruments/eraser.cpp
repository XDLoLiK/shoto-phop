#include "eraser.hpp"

Eraser::Eraser(const std::string& icon, int x, int y):
	Instrument(icon, x, y),
	m_curPoint ({-1, -1}),
	m_prevPoint({-1, -1})
{

}

Eraser::~Eraser()
{

}

bool Eraser::mouseLeave(Surface*, booba::Event*)
{
	m_mouseIsPressed = false;

	return true;
}

bool Eraser::apply(Surface* surface, booba::Event* event)
{
	bool res = false;

	switch (event->type) {
		case booba::EventType::MousePressed:
			if (event->Oleg.mbedata.button == booba::MouseButton::Left) {
				m_mouseIsPressed = true;
				m_curPoint = {event->Oleg.mbedata.x, event->Oleg.mbedata.y};
				this->drawPoint(surface, m_curPoint);
			}

			res = true;
			break;

		case booba::EventType::MouseReleased:
			if (m_mouseIsPressed) {
				m_mouseIsPressed = false;
				m_prevPoint = m_curPoint;
				m_curPoint  = {event->Oleg.mbedata.x, event->Oleg.mbedata.y};
				this->drawLine(surface);
			}

			res = true;
			break;

		case booba::EventType::MouseMoved:
			m_prevPoint = m_curPoint;
			m_curPoint  = {event->Oleg.motion.x, event->Oleg.motion.y};	
			if (m_mouseIsPressed) {
				this->drawLine(surface);
			}

			res = true;
			break;

		case booba::EventType::NoEvent:
		case booba::EventType::ButtonClicked:
		case booba::EventType::ScrollbarMoved:
		case booba::EventType::CanvasMPressed:
		case booba::EventType::CanvasMReleased:
		case booba::EventType::CanvasMMoved:

		default:
			break;
	}

	return res;
}

void Eraser::drawPoint(Surface* surface, const std::pair<int, int>& point)
{
	int width  = 0;
	int height = 0;
	Color* pixmap = surface->getPixmap(&width, &height);
	
	int x1 = std::max(0,     point.first - m_brushSize);
	int x2 = std::min(width, point.first + m_brushSize);

	int y1 = std::max(0,      point.second - m_brushSize);
	int y2 = std::min(height, point.second + m_brushSize);

	for (int y = y1; y < y2; y++) {
		for (int x = x1; x < x2; x++) {
			pixmap[width * y + x] = m_eraseColor;
		}
	}
}

void Eraser::drawLine(Surface* surface)
{
	// Bresenham's line algorithm
	int y2 = m_curPoint.second;
	int y1 = m_prevPoint.second;

	int x2 = m_curPoint.first;
	int x1 = m_prevPoint.first;

    const bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
    if(steep) {
		std::swap(x1, y1);
        std::swap(x2, y2);
    }

    if(x1 > x2) {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }

    const int dx = x2 - x1;
    const int dy = std::abs(y2 - y1);

    float error = static_cast<float>(dx) / 2.0f;
    const int ystep = (y1 < y2) ? 1 : -1;

    int x = x1;
    int y = y1;
    const int maxX = x2;

    for( ; x < maxX; x++) {
		if(steep) drawPoint(surface, {y, x});
        else      drawPoint(surface, {x, y});

        error -= static_cast<float>(dy);
        if(error < 0) {
            y += ystep;
            error += static_cast<float>(dx);
        }
    }
}
