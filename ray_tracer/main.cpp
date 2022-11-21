#include "scene.hpp"
#include "sphere.hpp"
#include "plane.hpp"

/*
 * TODO:
 * -Custom frame position for scene
 * -Objects, frame and camera rotation
 */

int main()
{
	Canvas canvas(600, 600);
	Scene  scene(&canvas, Scene::Camera(0.0, 0.0, 1.0));

	scene.addLightSource(Scene::LightSource(  0.0, 20.0, -20.0));
	scene.addLightSource(Scene::LightSource(-20.0, 20.0,   0.0));
	scene.addLightSource(Scene::LightSource( 20.0, 20.0,   0.0));

	Sphere ivorySphere(-3.0, -1.5, -8.0, 1.0, ivory(Color(0.4, 0.4, 0.3, 1.0)));
	scene.addObject(&ivorySphere);

	Sphere redSphere(-1.0, -1.5, -6.0, 1.0, rubber(red));
	scene.addObject(&redSphere);

	Sphere greenSphere(1.5, -1.5, -9.0, 2.0, rubber(green));
	scene.addObject(&greenSphere);

	Sphere glassSphere(0.0, -1.5, -4.0, 1.0, glass(white));
	scene.addObject(&glassSphere);

	Sphere mirrorSphere(-1.0, 4.0, -12.0, 3.0, mirror(white));
	scene.addObject(&mirrorSphere);

	Plane ground(Vector3(0.0, -5.0, 0.0), Vector3(-1.5, -5.0, 2.0), 
		         Vector3(1.5, -5.0, 3.0), plain(blue));
	scene.addObject(&ground);

	while (canvas.isOpen()) {
		canvas.clearRender();
		Event event{};
		event.poll();
		canvas.processEvent(event);
		scene.render();
		canvas.presentRender();
	}

	return 0;
}
