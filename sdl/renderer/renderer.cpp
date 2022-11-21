#include "renderer.hpp"

Renderer::Renderer(Window* window)
{
	if (!window)
		return;

	SDL_RendererFlags flags = SDL_RENDERER_ACCELERATED;
	m_realRenderer = SDL_CreateRenderer(window->getRealWindow(), -1, flags);
	if (!m_realRenderer)
		std::cout << SDL_GetError() << std::endl;
}

bool Renderer::setRenderTarget(Window* window)
{
	if (!window) {
		std::cout << "No target was provided" << std::endl;
		return false;
	}

	if (m_realRenderer) {
		std::cout << "The target has already been set" << std::endl;
		return false;
	}

	SDL_RendererFlags flags = SDL_RENDERER_ACCELERATED;
	m_realRenderer = SDL_CreateRenderer(window->getRealWindow(), -1, flags);
	if (!m_realRenderer)
		std::cout << SDL_GetError() << std::endl;

	return true;
}

Renderer::~Renderer()
{
	this->destroy();
}

Renderer& Renderer::operator=(Renderer&& other)
{
	this->destroy();
	this->m_realRenderer = other.m_realRenderer;
	other.m_realRenderer = nullptr;

	return *this;
}

Renderer::Renderer(Renderer&& other)
{
	this->m_realRenderer = other.m_realRenderer;
	other.m_realRenderer = nullptr;
}

void Renderer::destroy()
{
	SDL_DestroyRenderer(m_realRenderer);
	m_realRenderer = nullptr;
}

void Renderer::clear()
{
	SDL_SetRenderDrawColor(m_realRenderer, 255, 255, 255, 255);
	SDL_RenderClear(m_realRenderer);
}

void Renderer::present()
{
	SDL_RenderPresent(m_realRenderer);
}

void Renderer::drawLine(int x1, int y1, int x2, int y2)
{
	SDL_RenderDrawLine(m_realRenderer, x1, y1, x2, y2);
}

void Renderer::setDrawColor(const Color& color)
{
	SDL_SetRenderDrawColor(m_realRenderer, color.r, color.g, color.b, color.a);
}

void Renderer::copyTexture(const Texture* texture, const Rect& dest, const Rect& src)
{
	if (!texture) {
		std::cout << "No texture provided" << std::endl;
		return;
	}

	SDL_Texture* realTexture = texture->getRealTexture();
	SDL_Rect destRect = {dest.x, dest.y, dest.w, dest.h};
	SDL_Rect srcRect  = {src.x,  src.y,  src.w,  src.h};

	SDL_RenderCopy(m_realRenderer, realTexture, &srcRect, &destRect);
}

SDL_Renderer* Renderer::getRealRenderer() const
{
	return m_realRenderer;
}
