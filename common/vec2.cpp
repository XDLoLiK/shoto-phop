#include "vec2.hpp"

Vec2::Vec2(long double x, long double y):
	m_x(x),
	m_y(y)
{

}

Vec2& Vec2::operator*=(long double scale)
{
	m_x *= scale;
	m_y *= scale;
	return *this;
}

Vec2 operator*(const Vec2& vec, long double num)
{
	Vec2 newVec = vec;
	newVec *= num;
	return newVec;
}

Vec2 operator*(long double num, const Vec2& vec)
{
	return vec * num;
}

long double dotProduct(const Vec2& vec1, const Vec2& vec2)
{
	return vec1.getX() * vec2.getX() + vec1.getY() * vec2.getY();
}

Vec2& Vec2::operator+=(const Vec2& vec)
{
	m_x += vec.getX();
	m_y += vec.getY();
	return *this;
}

Vec2 operator+(const Vec2& vec1, const Vec2& vec2)
{
	Vec2 newVec = vec1;
	newVec += vec2;
	return newVec;
}

Vec2& Vec2::operator-=(const Vec2& vec)
{
	m_x -= vec.getX();
	m_y -= vec.getY();
	return *this;	
}

Vec2 operator-(const Vec2& vec1, const Vec2& vec2)
{
	Vec2 newVec = vec1;
	newVec -= vec2;
	return newVec;
}

Vec2 operator-(const Vec2& vec)
{
	return -1 * vec;
}

void Vec2::normalize()
{
	long double len = this->getLength();
	m_x /= len;
	m_y /= len;
}

Vec2 normalized(const Vec2& vec)
{
	long double len = vec.getLength();
	return Vec2(vec.getX() / len, vec.getY() / len);
}

long double Vec2::getX() const
{
	return m_x;
}

long double Vec2::getY() const
{
	return m_y;
}

long double Vec2::getLength() const
{
	return sqrtl(powl(m_x, 2) + powl(m_y, 2));
}

long double cos(const Vec2& vec1, const Vec2& vec2)
{
	long double numerator = vec1.getX() * vec2.getX() + 
	                        vec1.getY() * vec2.getY();

	long double denominator = vec1.getLength() * vec2.getLength();
	return equals(denominator, 0.0) ? INFINITY : numerator / denominator;
}
