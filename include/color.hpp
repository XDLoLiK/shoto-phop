#ifndef COLOR_HPP
#define COLOR_HPP

using color_t = unsigned char;

struct Color {
	color_t r = 0;
	color_t g = 0;
	color_t b = 0;
	color_t a = 0;

	bool operator==(const Color& second)
	{
		if (this->r != second.r) return false;
		if (this->g != second.g) return false;
		if (this->b != second.b) return false;
		if (this->a != second.a) return false;

		return true;
	}
};

constexpr Color black = {0,   0,   0,   255};
constexpr Color white = {255, 255, 255, 255};
constexpr Color red   = {255, 0,   0,   255};
constexpr Color green = {0,   255, 0,   255};
constexpr Color blue  = {0,   0,   255, 255};

constexpr Color buttonGrey      = {77,  77,  77,  255};
constexpr Color backgroundGrey  = {63,  63,  63,  255};

#endif // COLOR_HPP
