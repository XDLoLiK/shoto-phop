#include "color.hpp"

Color::Color(color_t rc, color_t gc, color_t bc, color_t ac)
{
	this->r = rc;
	this->g = gc;
	this->b = bc;
	this->a = ac;
}

Color::Color(uint32_t color)
{
	const uint32_t rmask = 0xFF000000;
	const uint32_t gmask = 0x00FF0000;
	const uint32_t bmask = 0x0000FF00;
	const uint32_t amask = 0x000000FF;

	this->r = static_cast<color_t>((color & rmask) >> 24);
	this->g = static_cast<color_t>((color & gmask) >> 16);
	this->b = static_cast<color_t>((color & bmask) >> 8);
	this->a = static_cast<color_t>((color & amask));
}

Color::~Color()
{

}

bool Color::operator==(const Color& second) const
{
	if (this->r != second.r) return false;
	if (this->g != second.g) return false;
	if (this->b != second.b) return false;
	if (this->a != second.a) return false;

	return true;
}

uint32_t Color::mapRGBA() const
{
	uint32_t res = 0;

	res |= static_cast<uint32_t>(this->a);
	res |= static_cast<uint32_t>(this->b) << 8;
	res |= static_cast<uint32_t>(this->g) << 16;
	res |= static_cast<uint32_t>(this->r) << 24;

	return res;
}
