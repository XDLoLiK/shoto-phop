#include "plugin.hpp"
#include "texture.hpp"

booba::Image::~Image()
{

}

booba::Tool::~Tool()
{

}

uint32_t Surface::getH()
{
	return static_cast<uint32_t>(this->getHeight());
}

uint32_t Surface::getW()
{
	return static_cast<uint32_t>(this->getWidth());
}

uint32_t Surface::getPixel(int32_t x, int32_t y)
{
	uint32_t* pixmap = reinterpret_cast<uint32_t*>(this->getPixmap());
	return pixmap[y * m_width + x];
}

void Surface::putPixel(uint32_t x, uint32_t y, uint32_t color)
{
	Color myColor = Color(color);
	Color* pixmap = this->getPixmap();
	pixmap[y * static_cast<uint32_t>(m_width) + x] = myColor;
}

uint32_t& Surface::operator()(uint32_t x, uint32_t y)
{
	uint32_t* pixmap = reinterpret_cast<uint32_t*>(this->getPixmap());
	return pixmap[y * static_cast<uint32_t>(m_width) + x];
}

const uint32_t& Surface::operator()(uint32_t x, uint32_t y) const
{
	uint32_t* pixmap = reinterpret_cast<uint32_t*>(const_cast<Surface*>(this)->getPixmap());
	return pixmap[y * static_cast<uint32_t>(m_width) + x];
}
