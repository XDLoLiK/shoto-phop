#include "scene.hpp"

Scene::Scene(const Canvas *canvas, const Camera &camera):
    canvas_(canvas),
    camera_(camera)
{

}

Scene::~Scene()
{
    lightSourcesList_.clear();
    objectsList_.clear();
}

void Scene::render()
{
    const Canvas *canvas   = canvas_;
    SDL_Renderer *renderer = canvas->renderer();
    SDL_Window   *window   = canvas->window();

    int width  = 0;
    int height = 0;
    SDL_GetWindowSize(window, &width, &height);

    for (int pixel = 0; pixel < height * width; pixel++) {
        int w = pixel % width;
        int h = pixel / width;

        long double curX = canvas->xToCU(w);
        long double curY = canvas->yToCU(h);
        long double curZ = 0.0; /* frame pos is 0.0 on z axis */

        Vector3 origin    = camera_.position();
        Vector3 point     = Vector3(curX, curY, curZ);
        Vector3 direction = normalized(point - origin);

        Color color = traceRay(origin, direction);
        SDL_SetRenderDrawColor(renderer, (color_t)(color.red()  * 255), (color_t)(color.green() * 255), 
                                         (color_t)(color.blue() * 255), (color_t)(color.alpha() * 255));
        SDL_RenderDrawPoint(renderer, w, h);
    }
}

Color Scene::traceRay(const Vector3 &origin, const Vector3 &direction, int depth) const
{
    auto [intersects, point, normal, material] = intersect(origin, direction);
    if (depth > 5 || !intersects)
        return white; /* background color */

    Vector3 reflectedDir = normalized(reflect(direction, normal));
    Vector3 refractedDir = normalized(refract(direction, normal, material.refractiveIndex()));

    Color reflectedColor = traceRay(point, reflectedDir, depth + 1);
    Color refractedColor = traceRay(point, refractedDir, depth + 1);

    long double diffuseIntensity  = 0.0l;
    long double specularIntensity = 0.0l;

    for (unsigned long n = 0; n < lightSourcesList_.size(); n++) {
        Vector3 lightDirection = lightSourcesList_.at(n).position() - point;
        
        auto [hasObstacle, obstaclePoint, obstacleNormal, obstacleMaterial] = intersect(point, lightDirection);
        long double obstacleDistance    = (obstaclePoint - point).length();
        long double lightSourceDistance = (lightSourcesList_.at(n).position() - point).length();

        if (hasObstacle && obstacleDistance < lightSourceDistance)
            continue;

        long double lightIntensity = lightSourcesList_.at(n).intensity();
        long double cosDiffuse     = cos(normal, lightDirection);
        long double cosSpecular    = cos(reflect(-lightDirection, normal), -direction);

        diffuseIntensity  += lightIntensity * std::max(0.0l, cosDiffuse);
        specularIntensity += lightIntensity * powl(std::max(0.0l, cosSpecular), material.specularExponent());
    }

    return material.color() * diffuseIntensity  * material.diffuseCoeff ()  +
                              specularIntensity * material.specularCoeff()  +
                              reflectedColor    * material.reflectCoeff ()  +
                              refractedColor    * material.refractCoeff ();
}

std::tuple<bool, Vector3, Vector3, Material> Scene::intersect(const Vector3 &origin, const Vector3 &direction) const
{
    long double minDistance = INFINITY;
    const Object *closestObject = nullptr;

    for (unsigned long n = 0; n < objectsList_.size(); n++) {
        auto [intersects, t] = objectsList_.at(n)->intersect(origin, direction);

        if (intersects && t < minDistance && !equals(t, 0.0)) {
            minDistance = t;
            closestObject = objectsList_.at(n);
        }
    }
    
    if (!isfinite(minDistance) || closestObject == nullptr)
        return {false, Vector3(0.0, 0.0, 0.0), Vector3(0.0, 0.0, 0.0), Material()};

    Vector3 point  = origin + direction * minDistance;
    Vector3 normal = closestObject->normal(point);
    return {true, point, normal, closestObject->material()};
}

void Scene::addLightSource(const LightSource &lightSource)
{
    lightSourcesList_.push_back(lightSource);
}

void Scene::addObject(const Object *obj)
{
    objectsList_.push_back(obj);
}

const std::vector<const Object *> &Scene::objectsList() const
{
    return objectsList_;
}

const std::vector<Scene::LightSource> &Scene::lightSourcesList() const
{
    return lightSourcesList_;
}

const Scene::Camera &Scene::camera() const
{
    return camera_;
}

const Canvas *Scene::canvas() const
{
    return canvas_;
}
