#include "plane.hpp"

Plane::Plane(const Vector3 &point1, const Vector3  &point2,
             const Vector3 &point3, const Material &material):
	point1_(point1),
	point2_(point2),
	point3_(point3),
	material_(material)
{

}

Plane::~Plane()
{

}

std::tuple<bool, long double> Plane::intersect(const Vector3 &origin, const Vector3 &direction) const
{
	Vector3 normal = this->normal(point3_);
	long double denomenator = dotProduct(direction, normal);

	if (equals(denomenator, 0.0l))
		return {false, 0.0l};

	long double numerator = dotProduct(point3_ - origin, normal);
	long double t = numerator / denomenator;

	if (t < 0.0)
		return {false, 0.0};
	return {true, t};
}

Vector3 Plane::normal(const Vector3 &) const
{
	Vector3 dir1 = point1_ - point3_;
	Vector3 dir2 = point2_ - point3_;

	return normalized(crossProduct(dir1, dir2));
}

const Material &Plane::material() const
{
	return material_;
}
