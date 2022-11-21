#pragma once

#include <algorithm>

using color_t = unsigned char;

class Color {
private:
    long double red_   = 1.0;
    long double green_ = 0;
    long double blue_  = 0;
    long double alpha_ = 1.0;

public:
    Color(long double red_,  long double green_, 
          long double blue_, long double alpha_);
    Color &operator+=(const Color &color);
    Color &operator*=(const Color &color);
    Color &operator+=(long double num);
    Color &operator-=(long double num);
    Color &operator*=(long double num);

    long double red()   const;
    long double green() const;
    long double blue()  const;
    long double alpha() const;
};

Color operator*(const Color &color, long double num);
Color operator*(long double num, const Color &color);
Color operator*(const Color &color1, const Color &color2);
Color operator+(const Color &color1, const Color &color2);
Color operator+(const Color &color, long double num);
Color operator+(long double num, const Color &color);
Color operator-(const Color &color, long double num);

const Color black = Color(0,    0,    0,    1.0);
const Color white = Color(1.0,  1.0,  1.0,  1.0);
const Color red   = Color(1.0,  0,    0,    1.0);
const Color green = Color(0,    1.0,  0,    1.0);
const Color blue  = Color(0,    0,    1.0,  1.0);
const Color grey  = Color(0.25, 0.25, 0.25, 1.0);
