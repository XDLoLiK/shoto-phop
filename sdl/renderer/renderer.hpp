#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SDL2/SDL.h>

#include "rect.hpp"
#include "window.hpp"
#include "texture.hpp"
	
class Renderer
{
public:
	Renderer(Window* window = nullptr);
	~Renderer();

	Renderer& operator=(const Renderer& other) = delete;
	Renderer(const Renderer& other)            = delete;

	Renderer& operator=(Renderer&& other);
	Renderer(Renderer&& other);

	bool setRenderTarget(Window* window);

	void destroy();

	void clear();
	void present();

	void copyTexture(const Texture* texture, const Rect& dest, const Rect& src);
	void drawLine(int x1, int y1, int x2, int y2);
	void setDrawColor(const Color& color);

	SDL_Renderer* getRealRenderer() const;

private:
	SDL_Renderer* m_realRenderer = nullptr;
};

#endif // RENDERER_HPP
