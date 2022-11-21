#include "material.hpp"

Material::Material(const Color &color,
	               long double refractiveIndex, long double specularExponent,
                   long double diffuseCoeff,    long double specularCoeff,
                   long double reflectCoeff,    long double refractCoeff):
	color_(color),
	refractiveIndex_(refractiveIndex),
	specularExponent_(specularExponent),
	diffuseCoeff_(diffuseCoeff),
	specularCoeff_(specularCoeff),
	reflectCoeff_(reflectCoeff),
	refractCoeff_(refractCoeff)
{

}

long double Material::refractiveIndex() const
{
	return refractiveIndex_;
}

long double Material::specularExponent() const
{
	return specularExponent_;
}

const Color &Material::color() const
{
	return color_;
}

long double Material::diffuseCoeff() const
{
	return diffuseCoeff_;
}

long double Material::specularCoeff() const
{
	return specularCoeff_;
}

long double Material::reflectCoeff() const
{
	return reflectCoeff_;
}

long double Material::refractCoeff() const
{
	return refractCoeff_;
}
