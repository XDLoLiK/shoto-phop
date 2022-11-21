#pragma once

#include "color.hpp"

class Material {
private:
	Color color_ = red;
	long double refractiveIndex_  = 0.0;
	long double specularExponent_ = 0.0;

	long double  diffuseCoeff_ = 0.0;
	long double specularCoeff_ = 0.0;
	long double  reflectCoeff_ = 0.0;
	long double  refractCoeff_ = 0.0;

public:
	Material(const Color &color = red,
		     long double refractiveIndex = 1.0, long double specularExponent = 1.0,
             long double diffuseCoeff    = 1.0, long double specularCoeff    = 1.0,
             long double reflectCoeff    = 1.0, long double refractCoeff     = 1.0);

	const Color &color           () const;
	long double refractiveIndex  () const;
	long double specularExponent () const;
	long double diffuseCoeff     () const;
	long double specularCoeff    () const;
	long double reflectCoeff     () const;
	long double refractCoeff     () const;
};

#define rubber(color) Material(color, 1.0,   10.0, 1.4, 0.3,  0.0,  0.0)
#define  glass(color) Material(color, 1.5,  125.0, 0.0, 0.9,  0.1,  0.8)
#define mirror(color) Material(color, 1.0, 1425.0, 0.0, 16.0, 0.93, 0.0)
#define  ivory(color) Material(color, 1.0,   50.0, 0.9, 0.5,  0.1,  0.0)
#define  plain(color) Material(color, 1.0,   10.0, 1.4, 0.8,  0.1,  0.0)
