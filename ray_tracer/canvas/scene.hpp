#pragma once

#include "canvas.hpp"
#include "vector.hpp"
#include "baseobj.hpp"

#include <vector>
#include <tuple>
#include <algorithm>

class Scene {
public:
    /* Camera exists only inside of a scene */
    class Camera {
    private:
        Vector3 position_ = Vector3(0.0, 0.0, 1.0);

    public:
        Camera(long double x, long double y,
               long double z);
        Camera(const Vector3 &vec);

        /* Getters */
        const Vector3 &position() const;
    };
    
    /* Light Sources exists only inside of a scene */
    class LightSource {
    private:
        Vector3 position_  = Vector3(1.0, 1.0, -1.0);
        Color color_ = white;
        long double intensity_ = 1.0;

    public:
        LightSource(long double x, long double y, 
                    long double z, const Color &color = Color(1.0, 1.0, 1.0, 1.0),
                    long double intensity = 1.0);
        LightSource(const Vector3 &position, const Color &color = Color(1.0, 1.0, 1.0, 1.0), 
                    long double intensity = 1.0);

        /* Getters */
        const Vector3 &position () const;
        const Color   &color    () const;
        long double   intensity () const;
    };

private:
    /* Parent canvas, may be NULL */
    const Canvas *canvas_ = nullptr;
    Camera camera_ = Camera(0.0, 0.0, 0.0);

    std::vector<LightSource>    lightSourcesList_ = std::vector<LightSource>    (0, LightSource(1.0, 1.0, -1.0));
    std::vector<const Object *> objectsList_      = std::vector<const Object *> (0);

    Color traceRay(const Vector3 &origin, const Vector3 &direction, int depth = 1) const;
    std::tuple<bool, Vector3, Vector3, Material> intersect(const Vector3 &origin, const Vector3 &direction) const;

public:
    Scene(const Canvas *canvas, const Camera &camera = Camera(0.0, 0.0, 0.0));
    Scene(const Scene &scene) = delete;
    Scene operator=(const Scene &scene) = delete;
    ~Scene();

    void render();
    void addObject(const Object *obj);
    void addLightSource(const LightSource &lightSource);

    /* Getters */
    const std::vector<const Object *> &objectsList()      const;
    const std::vector<LightSource>    &lightSourcesList() const;
    const Camera                      &camera()           const;
    const Canvas                      *canvas()           const;
};
