#include "vec3.hpp"

Vec3::Vec3(long double x, long double y, long double z):
	m_x(x),
	m_y(y),
	m_z(z)
{

}

Vec3& Vec3::operator*=(long double scale)
{
	m_x *= scale;
	m_y *= scale;
	m_z *= scale;
	return *this;
}

Vec3 operator*(const Vec3& vec, long double num)
{
	Vec3 newVec = vec;
	newVec *= num;
	return newVec;
}

Vec3 operator*(long double num, const Vec3& vec)
{
	return vec * num;
}

long double dotProduct(const Vec3& vec1, const Vec3& vec2)
{
	return vec1.getX() * vec2.getX() + 
	       vec1.getY() * vec2.getY() + vec1.getZ() * vec2.getZ();
}

Vec3 crossProduct(const Vec3& vec1, const Vec3& vec2)
{
	long double newX = vec1.getY() * vec2.getZ() - vec1.getZ() * vec2.getY();
	long double newY = vec1.getZ() * vec2.getX() - vec1.getX() * vec2.getZ();
	long double newZ = vec1.getX() * vec2.getY() - vec1.getY() * vec2.getX();
	return Vec3(newX, newY, newZ);
}

Vec3& Vec3::operator+=(const Vec3& vec)
{
	m_x += vec.getX();
	m_y += vec.getY();
	m_z += vec.getZ();
	return *this;
}

Vec3 operator+(const Vec3& vec1, const Vec3& vec2)
{
	Vec3 newVec = vec1;
	newVec += vec2;
	return newVec;
}

Vec3& Vec3::operator-=(const Vec3& vec)
{
	m_x -= vec.getX();
	m_y -= vec.getY();
	m_z -= vec.getZ();
	return *this;	
}

Vec3 operator-(const Vec3& vec1, const Vec3& vec2)
{
	Vec3 newVec = vec1;
	newVec -= vec2;
	return newVec;	
}

Vec3 operator-(const Vec3& vec)
{
	return -1 * vec;
}

void Vec3::normalize()
{
	long double len = this->getLength();
	m_x /= len;
	m_y /= len;
	m_z /= len;
}

Vec3 normalized(const Vec3& vec)
{
	long double len = vec.getLength();
	return Vec3(vec.getX() / len, vec.getY() / len, vec.getZ() / len);
}

long double Vec3::getX() const
{
	return m_x;
}

long double Vec3::getY() const
{
	return m_y;
}

long double Vec3::getZ() const
{
	return m_z;
}

long double Vec3::getLength() const
{
	return sqrtl(powl(m_x, 2) + powl(m_y, 2) + powl(m_z, 2));
}

long double cos(const Vec3& vec1, const Vec3& vec2)
{
	long double numerator   = vec1.getX() * vec2.getX() + 
	                          vec1.getY() * vec2.getY() + 
	                          vec1.getZ() * vec2.getZ();

	long double denominator = vec1.getLength() * vec2.getLength();
	return equals(denominator, 0.0) ? INFINITY : numerator / denominator;
}