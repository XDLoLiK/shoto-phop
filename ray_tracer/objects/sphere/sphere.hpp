#pragma once

#include "baseobj.hpp"

class Sphere : public Object {
private:
	Vector3     center_   = Vector3(0.0, 0.0, 0.0); 
	long double radius_   = 0.0;
	Material    material_ = Material();

	enum SolutionsNumber {
		e_infRoots = -1,
		e_noRoots  =  0,
		e_oneRoot  =  1,
		e_twoRoots =  2
	};

	std::tuple<enum SolutionsNumber, long double, long double> solveQuadratic(long double a,
		                                                                      long double b,
		                                                                      long double c) const;

public:
	Sphere(long double x, long double y,
		   long double z, long double r, const Material &material = Material());
	Sphere(const Vector3 &vec, long double r,
		   const Material  &material = Material());
	~Sphere() override;

	std::tuple<bool, long double> intersect(const Vector3 &origin, const Vector3 &direction) const override;
	Vector3 normal(const Vector3 &point) const override;

	/* Getters */
	const Vector3  &center   () const;
	long double    radius    () const;
	const Material &material () const override;
};
