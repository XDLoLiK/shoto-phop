#ifndef VEC2_HPP
#define VEC2_HPP

#include "maths.hpp"

class Vec2 {
public:
	Vec2(long double x,  long double y);

	Vec2 &operator*=(long double scale);
	Vec2 &operator+=(const Vec2 &vec);
	Vec2 &operator-=(const Vec2 &vec);

	void normalize();

	long double getX()      const;
	long double getY()      const;
	long double getLength() const;

private:
	long double m_x = 0.0;
	long double m_y = 0.0;
};

Vec2 normalized(const Vec2 &vec);

Vec2 operator*(const Vec2 &vec, long double num);
Vec2 operator*(long double num, const Vec2 &vec);

long double dotProduct(const Vec2 &vec1, const Vec2 &vec2);

Vec2 operator+(const Vec2 &vec1, const Vec2 &vec2);

Vec2 operator-(const Vec2 &vec1, const Vec2 &vec2);
Vec2 operator-(const Vec2 &vec);

long double cos(const Vec2 &vec1, const Vec2 &vec2);

#endif // VEC2_HPP
