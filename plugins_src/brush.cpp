#include "brush.hpp"


extern booba::ApplicationContext* booba::APPCONTEXT;
const char texture[] = "brush.png";


BrushTool::BrushTool():
	m_curPoint ({-1, -1}),
	m_prevPoint({-1, -1})
{

}

BrushTool::~BrushTool()
{

}

void BrushTool::apply(booba::Image* image, const booba::Event* event)
{
	m_drawColor = booba::APPCONTEXT->fgColor;

	switch (event->type) {
		case booba::EventType::MousePressed:
			if (event->Oleg.mbedata.button == booba::MouseButton::Left) {
				m_mouseIsPressed = true;
				m_curPoint = {static_cast<int>(event->Oleg.mbedata.x), 
					          static_cast<int>(event->Oleg.mbedata.y)};
				this->drawPoint(image, m_curPoint);
			}

			break;

		case booba::EventType::MouseReleased:
			if (m_mouseIsPressed) {
				m_mouseIsPressed = false;
				m_prevPoint = m_curPoint;
				m_curPoint  = {static_cast<int>(event->Oleg.mbedata.x), 
					          static_cast<int>(event->Oleg.mbedata.y)};
				this->drawLine(image);
			}

			break;

		case booba::EventType::MouseMoved:
			if (m_mouseIsPressed) {
				m_prevPoint = m_curPoint;
				m_curPoint  = {event->Oleg.motion.x, event->Oleg.motion.y};	
				this->drawLine(image);
			}

			break;

		case booba::EventType::CanvasMLeft:
			m_mouseIsPressed = false;
			break;

		case booba::EventType::SliderMoved:
			if (event->Oleg.smedata.id == m_sizeSlider) {
				m_brushSize = event->Oleg.smedata.value;
			}
			break;

		case booba::EventType::NoEvent:
		case booba::EventType::ButtonClicked:
		case booba::EventType::CanvasMPressed:
		case booba::EventType::CanvasMReleased:
		case booba::EventType::CanvasMMoved:

		default:
			break;
	}
}

const char* BrushTool::getTexture()
{
	return texture;
}

void BrushTool::buildSetupWidget()
{
	booba::setToolBarSize(200, 50);
	m_sizeSlider = booba::createSlider(10, 10, 140, 20, 2, 20, 4);
	booba::createLabel(160, 10, 35, 20, "Size");
}

void BrushTool::drawPoint(booba::Image* image, const std::pair<int, int>& point)
{
	int width  = static_cast<int>(image->getW());
	int height = static_cast<int>(image->getH());

	int x1 = std::max(point.first - m_brushSize, 0);
	int x2 = std::min(width, point.first + m_brushSize);

	int y1 = std::max(point.second - m_brushSize, 0);
	int y2 = std::min(height, point.second + m_brushSize);

	for (int y = y1; y < y2; y++) {
		for (int x = x1; x < x2; x++) {
			if (std::pow(point.first - x, 2) + std::pow(point.second - y, 2) <= std::pow(m_brushSize, 2)) {
				image->setPixel(x, y, m_drawColor);
			}
		}
	}
}

void BrushTool::drawLine(booba::Image* image)
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
		if(steep) drawPoint(image, {y, x});
        else      drawPoint(image, {x, y});

        error -= static_cast<float>(dy);
        if(error < 0) {
            y += ystep;
            error += static_cast<float>(dx);
        }
    }
}

void booba::init_module()
{
    BrushTool* brushTool = new BrushTool();
    booba::addTool(brushTool);
}
