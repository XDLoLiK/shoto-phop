#pragma once

#include <SDL2/SDL.h>
#include <iostream>

#include "event.hpp"

class Canvas {
private:
    SDL_Window   *window_   = nullptr;
    SDL_Renderer *renderer_ = nullptr;

    long double xMin_ = 0.0;
    long double xMax_ = 0.0;
    long double yMin_ = 0.0;
    long double yMax_ = 0.0;

    bool isOpen_ = true;

public:
    Canvas(int width = 800, int height = 600,
           long double xMin = -1.0, long double xMax = 1.0, 
           long double yMin = -1.0, long double yMax = 1.0);
    Canvas(const Canvas &window) = delete;
    Canvas &operator=(const Canvas &window) = delete;
    ~Canvas();

    /* Event handler */
    void processEvent(const Event &event);

    /* Render managment */
    void clearRender()   const;
    void presentRender() const;

    /* Converters */
    int xToPixels(long double x) const;
    int yToPixels(long double y) const;
    long double xToCU(int x) const;
    long double yToCU(int y) const;

    /* Getters */
    bool isOpen() const;
    long double xMin() const;
    long double xMax() const;
    long double yMin() const;
    long double yMax() const;
    SDL_Window   *window()   const;
    SDL_Renderer *renderer() const;
};
