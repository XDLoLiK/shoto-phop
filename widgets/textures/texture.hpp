#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "rect.hpp"

class Texture
{
public:
	Texture(const std::string& img = "");
	~Texture();

	Texture& operator=(const Texture& other) = delete;
	Texture(const Texture& other)            = delete;

	Texture(Texture&& temp);
	Texture& operator=(Texture&& temp);

	const Rect& getBounds() const;
	SDL_Texture* getRealTexture() const;

private:
	SDL_Surface* m_realSurface = nullptr;
	SDL_Texture* m_realTexture = nullptr;

	Rect m_bounds = {0, 0, 0, 0};
};

#endif // TEXTURE_HPP
