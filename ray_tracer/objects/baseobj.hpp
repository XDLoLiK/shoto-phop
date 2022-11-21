#pragma once

#include "vector.hpp"
#include "material.hpp"

#include <tuple>

class Object {
public:
	Object() {};
	virtual ~Object() {};

	virtual std::tuple<bool, long double> intersect(const Vector3 &origin, const Vector3 &direction) const = 0;
	virtual Vector3 normal(const Vector3 &point) const = 0;
	virtual const Material &material() const = 0;
};
