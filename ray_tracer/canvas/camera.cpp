#include "scene.hpp"

Scene::Camera::Camera(long double x, long double y,
	                  long double z):
	position_(Vector3(x, y, z))
{

}

Scene::Camera::Camera(const Vector3 &vec):
	position_(vec)
{

}

const Vector3 &Scene::Camera::position() const
{
	return position_;
}
