#pragma once

#include "baseobj.hpp"

class Plane : public Object {
private:
	Vector3 point1_ = Vector3(0.0, 0.0, 0.0);
	Vector3 point2_ = Vector3(0.0, 0.0, 0.0);
	Vector3 point3_ = Vector3(0.0, 0.0, 0.0);
	Material material_ = Material();

public:
	Plane(const Vector3  &point1, const Vector3  &point2,
		  const Vector3  &point3, const Material &material = Material());
	~Plane() override;

	std::tuple<bool, long double> intersect(const Vector3 &origin, const Vector3 &direction) const override;
	Vector3 normal(const Vector3 &) const override;

	/* Getters */
	const Material &material () const override;
};
