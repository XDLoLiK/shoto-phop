#ifndef VEC3_HPP
#define VEC3_HPP

#include "maths.hpp"

class Vec3 {
public:
	Vec3(long double x,  long double y,  long double z);

	Vec3 &operator*=(long double scale);
	Vec3 &operator+=(const Vec3 &vec);
	Vec3 &operator-=(const Vec3 &vec);

	void normalize();

	long double getX()      const;
	long double getY()      const;
	long double getZ()      const;
	long double getLength() const;

private:
	long double m_x = 0.0;
	long double m_y = 0.0;
	long double m_z = 0.0;
};

Vec3 normalized(const Vec3 &vec);

Vec3 operator*(const Vec3 &vec, long double num);
Vec3 operator*(long double num, const Vec3 &vec);

long double dotProduct(const Vec3 &vec1, const Vec3 &vec2);
Vec3 crossProduct(const Vec3 &vec1, const Vec3 &vec2);

Vec3 operator+(const Vec3 &vec1, const Vec3 &vec2);

Vec3 operator-(const Vec3 &vec1, const Vec3 &vec2);
Vec3 operator-(const Vec3 &vec);

long double cos(const Vec3 &vec1, const Vec3 &vec2);

#endif // VEC3_HPP