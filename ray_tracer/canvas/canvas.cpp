#include "canvas.hpp"

Canvas::Canvas(int width, int height,
	           long double xMin, long double xMax, 
	           long double yMin, long double yMax):
	xMin_(xMin),
	xMax_(xMax),
	yMin_(yMin),
	yMax_(yMax)
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");

	window_   = SDL_CreateWindow("Canvas", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
	renderer_ = SDL_CreateRenderer(window_, -1, 0); 

	isOpen_ = true;
}

Canvas::~Canvas()
{
	xMin_ = xMax_ = yMin_ = yMax_ = 0.0;

	isOpen_ = false;

	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	SDL_Quit();
}

void Canvas::processEvent(const Event &event)
{
	switch (event.type()) {
		case SDL_QUIT:
			isOpen_ = false;
			break;

		default:
			break;
	}
}

void Canvas::clearRender() const
{
	SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
	SDL_RenderClear(renderer_);
}

void Canvas::presentRender() const
{
	SDL_RenderPresent(renderer_);
}

bool Canvas::isOpen() const
{
	return isOpen_;
}

long double Canvas::xMin() const
{
	return xMin_;
}

long double Canvas::xMax() const
{
	return xMax_;
}

long double Canvas::yMin() const
{
	return yMin_;
}

long double Canvas::yMax() const
{
	return yMax_;
}

SDL_Window *Canvas::window() const
{
	return window_;
}

SDL_Renderer *Canvas::renderer() const
{
	return renderer_;
}

int Canvas::xToPixels(long double x) const
{
	int width = 0;
	SDL_GetWindowSize(window_, &width, nullptr);
	return (int)((x - xMin_) / (xMax_ - xMin_) * width);
}

int Canvas::yToPixels(long double y) const
{
	int height = 0;
	SDL_GetWindowSize(window_, nullptr, &height);
	return (int)(((yMax_ - yMin_) - (y - yMin_)) / (yMax_ - yMin_) * height); 
}

long double Canvas::xToCU(int x) const
{
	int width = 0;
	SDL_GetWindowSize(window_, &width, nullptr);
	return (double)x / (double)width * (xMax_ - xMin_) + xMin_; 
}

long double Canvas::yToCU(int y) const
{
	int height = 0;
	SDL_GetWindowSize(window_, nullptr, &height);
	return (yMax_ - yMin_) - (double)y / (double)height * (yMax_ - yMin_) + yMin_; 
}
