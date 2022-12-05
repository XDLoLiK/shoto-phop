#include "color_chooser.hpp"
#include "app.hpp"

ColorPicker::ColorPicker(const Rect& bounds, Widget* parent):
	Widget(bounds, parent)
{
	const double toneWidWidthScale  = 0.90;
	const double colorWidWidthScale = 0.08;
	const double colorOffsetScale   = 0.92;

	m_colorPickerTone  = Surface(m_bounds.w * toneWidWidthScale,  m_bounds.h);
	m_colorPickerColor = Surface(m_bounds.w * colorWidWidthScale, m_bounds.h);

	this->setFrameColor(black);
	this->fillWithTones();
	this->fillWithColors();
}

ColorPicker::~ColorPicker()
{

}

Color ColorPicker::getColor()
{
	return m_color;
}

void ColorPicker::fillWithColors()
{
	int v = 100;
	int s = 100;
	int h = 360;

	int maxH = 360;

	int width  = 0;
	int height = 0;
	Color* pixmap = m_colorPickerColor.getPixmap(&width, &height);

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			double relH = static_cast<double>(y) / static_cast<double>(height);
			h = maxH - static_cast<int>(maxH * relH);

			Color curColor = fromHSVtoRGBA(h, s, v);
			pixmap[y * width + x] = curColor;
		}
	}
}

void ColorPicker::fillWithTones()
{
	int v = 100;
	int s = 0;
	int h = m_h;

	int maxV = 100;
	int maxS = 100;

	int width  = 0;
	int height = 0;
	Color* pixmap = m_colorPickerTone.getPixmap(&width, &height);

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			double relV = static_cast<double>(y) / static_cast<double>(height);
			double relS = static_cast<double>(x) / static_cast<double>(width);

			v = maxV - static_cast<int>(maxV * relV);
			s =        static_cast<int>(maxS * relS);

			Color curColor = fromHSVtoRGBA(h, s, v);
			pixmap[y * width + x] = curColor;
		}
	}
}

Color fromHSVtoRGBA(int h, int s, int v)
{
	double S = s / 100.0;
    double V = v / 100.0;

    double C = S * V;
    double X = C * (1 - std::abs(std::fmod(h / 60.0, 2) - 1));
    double m = V - C;

    double r = 0;
    double g = 0;
    double b = 0;
    
    if (h >= 0 && h < 60) {
        r = C;
        g = X;
        b = 0;
    }
    else if (h >= 60 && h < 120) {
        r = X;
        g = C;
        b = 0;
    }
    else if (h >= 120 && h < 180) {
        r = 0;
        g = C;
        b = X;
    }
    else if (h >= 180 && h < 240) {
        r = 0;
        g = X;
        b = C;
    }
    else if (h >= 240 && h < 300) {
        r = X;
        g = 0;
        b = C;
    }
    else if (h >= 300 && h <= 360) {
        r = C;
        g = 0;
        b = X;
    }

    color_t R = (r + m) * 255;
    color_t G = (g + m) * 255;
    color_t B = (b + m) * 255;
    color_t A =           255;

    Color color = {};
    color.r = R;
    color.g = G;
    color.b = B;
    color.a = A;

    return color;
}

void ColorPicker::draw()
{
	Renderer* renderer = getApp()->getRenderer();

	static int prevH = 0;
	if (prevH != m_h) {
		prevH = m_h;
		this->fillWithTones();
		this->fillWithColors();
	}

	const double toneWidWidthScale  = 0.90;
	const double colorWidWidthScale = 0.08;
	const double colorOffsetScale   = 0.92;

	Rect toneBounds  = {m_bounds.x,                                 m_bounds.y, m_bounds.w * toneWidWidthScale,  m_bounds.h};
	Rect colorBounds = {m_bounds.x + m_bounds.w * colorOffsetScale, m_bounds.y, m_bounds.w * colorWidWidthScale, m_bounds.h};

	Rect m_copyToneBounds  = {0, 0, m_colorPickerTone.getWidth(),  m_colorPickerTone.getHeight()};
	Rect m_copyColorBounds = {0, 0, m_colorPickerColor.getWidth(), m_colorPickerColor.getHeight()};

	Texture* toneTexture = new Texture(m_colorPickerTone);
	renderer->copyTexture(toneTexture, toneBounds, m_copyToneBounds);
	delete toneTexture;

	Texture* colorTexture = new Texture(m_colorPickerColor);
	renderer->copyTexture(colorTexture, colorBounds, m_copyColorBounds);
	delete colorTexture;

	this->drawFrame(m_bounds);
}

bool intersectsBounds(const Vec2& point, const Rect& bounds)
{
	if (point.getX() < bounds.x || 
		point.getX() > bounds.x + bounds.w)
	{
		return false;
	}

	if (point.getY() < bounds.y || 
		point.getY() > bounds.y + bounds.h)
	{
		return false;
	}

	return true;
}

bool ColorPicker::intersects(const Vec2& point)
{
	if (point.getX() < m_bounds.x || 
		point.getX() > m_bounds.x + m_bounds.w)
	{
		return false;
	}

	if (point.getY() < m_bounds.y || 
		point.getY() > m_bounds.y + m_bounds.h)
	{
		return false;
	}

	return true;
}

bool ColorPicker::onMouseMove(const Vec2& point, const Vec2& motion)
{
	if (m_isHidden) {
		return false;
	}
}

bool ColorPicker::onButtonClick(MouseButton button, const Vec2& point)
{
	if (m_isHidden) {
		return false;
	}
}

bool ColorPicker::onButtonRelease(MouseButton button, const Vec2& point)
{
	if (m_isHidden) {
		return false;
	}

	if (button != SDL_BUTTON_LEFT) {
		return false;
	}

	const double toneWidWidthScale  = 0.90;
	const double colorWidWidthScale = 0.08;
	const double colorOffsetScale   = 0.92;

	Rect toneBounds  = {m_bounds.x,                                 m_bounds.y, m_bounds.w * toneWidWidthScale,  m_bounds.h};
	Rect colorBounds = {m_bounds.x + m_bounds.w * colorOffsetScale, m_bounds.y, m_bounds.w * colorWidWidthScale, m_bounds.h};

	if (intersectsBounds(point, toneBounds)) {
		int width  = 0;
		int height = 0;
		Color* pixmap = m_colorPickerTone.getPixmap(&width, &height);

		int x = static_cast<int>(point.getX()) - m_bounds.x;
		int y = static_cast<int>(point.getY()) - m_bounds.y;

		m_color = pixmap[y * width + x];
	}

	if (intersectsBounds(point, colorBounds)) {
		double offset = point.getY() - static_cast<double>(m_bounds.y);
		double rel    = offset / static_cast<double>(m_bounds.h);

		double newH = 360.0 * rel;
		m_h = static_cast<int>(newH);

		std::cout << m_h << std::endl;
	}
}

bool ColorPicker::onKeyPress(Key key)
{
	if (m_isHidden) {
		return false;
	}
}

bool ColorPicker::onKeyRelease(Key key)
{
	if (m_isHidden) {
		return false;
	}
}

bool ColorPicker::onTick(Time time)
{
	if (m_isHidden) {
		return false;
	}

	this->draw();
	return true;
}
