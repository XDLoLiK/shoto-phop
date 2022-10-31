#include "app.hpp"
#include "texture.hpp"


extern App* __theApp__;


Texture::Texture(const std::string& img)
{
	SDL_Renderer* renderer = __theApp__->renderer.getRealRenderer();

	m_realSurface = IMG_Load(img.c_str());
	m_realTexture = SDL_CreateTextureFromSurface(renderer, m_realSurface);

	m_bounds = {0, 0, m_realSurface->w, m_realSurface->h};
}

Texture::~Texture()
{
	SDL_FreeSurface(m_realSurface);
	SDL_DestroyTexture(m_realTexture);
}

Texture::Texture(Texture&& temp)
{
	this->m_realSurface = temp.m_realSurface;
	this->m_realTexture = temp.m_realTexture;
	this->m_bounds      = temp.m_bounds;

	temp.m_realSurface = nullptr;
	temp.m_realTexture = nullptr;
}

Texture& Texture::operator=(Texture&& temp)
{
	SDL_FreeSurface(m_realSurface);
	SDL_DestroyTexture(m_realTexture);

	this->m_realSurface = temp.m_realSurface;
	this->m_realTexture = temp.m_realTexture;
	this->m_bounds      = temp.m_bounds;

	temp.m_realSurface = nullptr;
	temp.m_realTexture = nullptr;

	return *this;
}

const Rect& Texture::getBounds() const
{
	return m_bounds;
}

SDL_Texture* Texture::getRealTexture() const
{
	return m_realTexture;
}
