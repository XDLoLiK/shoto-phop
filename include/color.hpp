#ifndef COLOR_HPP
#define COLOR_HPP

#include <cstdint>
#include <iostream>

using color_t = unsigned char;

struct Color {
	Color(color_t rc, color_t gc, color_t bc, color_t ac);
	Color(uint32_t color = 0);
	~Color();

	color_t r = 0;
	color_t g = 0;
	color_t b = 0;
	color_t a = 0;

	bool operator==(const Color& second) const;
	uint32_t mapRGBA() const;
};

const Color black = {0,   0,   0,   255};
const Color white = {255, 255, 255, 255};
const Color red   = {255, 0,   0,   255};
const Color green = {0,   255, 0,   255};
const Color blue  = {0,   0,   255, 255};

const Color buttonGrey      = {77,  77,  77,  255};
const Color backgroundGrey  = {63,  63,  63,  255};

#endif // COLOR_HPP
