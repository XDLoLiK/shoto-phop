#include "color.hpp"

Color::Color(long double red,  long double green, 
             long double blue, long double alpha):
    red_  ((red   > 1.0) ? 1.0 : (red   < 0.0) ? 0.0 : red),
    green_((green > 1.0) ? 1.0 : (green < 0.0) ? 0.0 : green),
    blue_ ((blue  > 1.0) ? 1.0 : (blue  < 0.0) ? 0.0 : blue),
    alpha_((alpha > 1.0) ? 1.0 : (alpha < 0.0) ? 0.0 : alpha)
{

}

long double Color::red() const
{
    return red_;
}

long double Color::green() const
{
    return green_;
}

long double Color::blue() const
{
    return blue_;
}

long double Color::alpha() const
{
    return alpha_;
}

Color &Color::operator*=(long double num)
{
    long double newRed   = red_   * num;
    long double newGreen = green_ * num;
    long double newBlue  = blue_  * num;
    long double newAlpha = alpha_ * num;

    red_   = (newRed   > 1.0) ? 1.0 : (newRed   < 0.0) ? 0.0 : newRed;
    green_ = (newGreen > 1.0) ? 1.0 : (newGreen < 0.0) ? 0.0 : newGreen;
    blue_  = (newBlue  > 1.0) ? 1.0 : (newBlue  < 0.0) ? 0.0 : newBlue;
    alpha_ = (newAlpha > 1.0) ? 1.0 : (newAlpha < 0.0) ? 0.0 : newAlpha;

    return *this;
}

Color &Color::operator*=(const Color &color)
{
    red_   *= color.red();
    green_ *= color.green();
    blue_  *= color.blue() ;
    alpha_ *= color.alpha();

    return *this;
}

Color operator*(const Color &color, long double num)
{
    Color newColor = color;
    newColor *= num;
    return newColor;
}

Color operator*(long double num, const Color &color)
{
    return color * num;
}

Color operator*(const Color &color1, const Color &color2)
{
    Color newColor = color1;
    newColor *= color2;
    return newColor;
}

Color &Color::operator+=(const Color &color)
{
    long double newRed   = color.red()   + red_;
    long double newGreen = color.green() + green_;
    long double newBlue  = color.blue()  + blue_;
    long double newAlpha = color.alpha() + alpha_;

    red_   = (newRed   > 1.0) ? 1.0 : newRed;
    green_ = (newGreen > 1.0) ? 1.0 : newGreen;
    blue_  = (newBlue  > 1.0) ? 1.0 : newBlue;
    alpha_ = (newAlpha > 1.0) ? 1.0 : newAlpha;

    return *this;
}

Color operator+(const Color &color1, const Color &color2)
{
    Color newColor = color1;
    newColor += color2;
    return newColor;
}

Color &Color::operator+=(long double num)
{
    long double newRed   = num + red_;
    long double newGreen = num + green_;
    long double newBlue  = num + blue_;
    long double newAlpha = num + alpha_;

    red_   = (newRed   > 1.0) ? 1.0 : (newRed   < 0.0) ? 0.0 : newRed;
    green_ = (newGreen > 1.0) ? 1.0 : (newGreen < 0.0) ? 0.0 : newGreen;
    blue_  = (newBlue  > 1.0) ? 1.0 : (newBlue  < 0.0) ? 0.0 : newBlue;
    alpha_ = (newAlpha > 1.0) ? 1.0 : (newAlpha < 0.0) ? 0.0 : newAlpha;

    return *this;   
}

Color operator+(const Color &color, long double num)
{
    Color newColor = color;
    newColor += num;
    return newColor;
}

Color operator+(long double num, const Color &color)
{
    return color + num;
}

Color &Color::operator-=(long double num)
{
    long double newRed   = red_   - num;
    long double newGreen = green_ - num;
    long double newBlue  = blue_  - num;
    long double newAlpha = alpha_ - num;

    red_   = (newRed   > 1.0) ? 1.0 : (newRed   < 0.0) ? 0.0 : newRed;
    green_ = (newGreen > 1.0) ? 1.0 : (newGreen < 0.0) ? 0.0 : newGreen;
    blue_  = (newBlue  > 1.0) ? 1.0 : (newBlue  < 0.0) ? 0.0 : newBlue;
    alpha_ = (newAlpha > 1.0) ? 1.0 : (newAlpha < 0.0) ? 0.0 : newAlpha;

    return *this;   
}

Color operator-(const Color &color, long double num)
{
    Color newColor = color;
    newColor -= num;
    return newColor;
}
