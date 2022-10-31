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

bool Renderer::setRenderWindow(Window* window)
{
	if (!window)
		return false;

	if (m_realRenderer)
		return false;

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

void Renderer::copyTexture(const Texture* texture, const Rect& bounds)
{
	SDL_Texture* realTexture = texture->getRealTexture();
	SDL_Rect destRect = {bounds.x, bounds.y, bounds.w, bounds.h};

	const Rect& textureRect = texture->getBounds();
	SDL_Rect srcRect  = {textureRect.x, textureRect.y, textureRect.w, textureRect.h};

	SDL_RenderCopy(m_realRenderer, realTexture, &srcRect, &destRect);
}

SDL_Renderer* Renderer::getRealRenderer() const
{
	return m_realRenderer;
}
