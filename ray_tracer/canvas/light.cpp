#include "scene.hpp"

Scene::LightSource::LightSource(long double x, long double y,
	                            long double z, const Color &color, 
	                            long double intensity):
	position_(Vector3(x, y, z)),
	color_(color),
	intensity_((intensity > 1.0) ? 1.0 : intensity)
{

}

Scene::LightSource::LightSource(const Vector3 &position, const Color &color,
	                            long double intensity):
	position_(position),
	color_(color),
	intensity_((intensity > 1.0) ? 1.0 : intensity)

{

}

const Vector3 &Scene::LightSource::position() const
{
	return position_;
}

const Color &Scene::LightSource::color() const
{
	return color_;
}

long double Scene::LightSource::intensity() const
{
	return intensity_;
}	
