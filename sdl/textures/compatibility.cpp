#include "plugin.hpp"
#include "texture.hpp"

size_t Surface::getH()
{
	return static_cast<size_t>(this->getHeight());
}

size_t Surface::getW()
{
	return static_cast<size_t>(this->getWidth());
}

uint32_t Surface::getPixel(size_t x, size_t y)
{
	Color* pixmap = this->getPixmap();
	Color myColor = pixmap[y * static_cast<size_t>(m_width) + x];
	return myColor.mapRGBA();
}

void Surface::setPixel(size_t x, size_t y, uint32_t color)
{
	Color myColor = Color(color);
	Color* pixmap = this->getPixmap();
	pixmap[y * static_cast<size_t>(m_width) + x] = myColor;
}
