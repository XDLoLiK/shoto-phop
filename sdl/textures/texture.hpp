#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "rect.hpp"
#include "color.hpp"
#include "plugin.hpp"

#define SURFACE_SIZE_MIN 1
#define NO_SKIN "skins/missing_texture.png"
#define NO_FRAME white

class Surface : public booba::Image
{
public:
	Surface(SDL_Surface* realSurface);
	Surface(int width = 0, int height = 0);
	Surface(const std::string& image);
	virtual ~Surface();

	Surface& operator=(const Surface& other) = delete;
	Surface(const Surface& other)            = delete;

	Surface(Surface&& temp);
	Surface& operator=(Surface&& temp);

	int getWidth()  const;
	int getHeight() const;

	Color* getPixmap(int* width = nullptr, int* height = nullptr);
	SDL_Surface* getRealSurface() const;
	void fillColor(const Color& color);

public: /* compatability */

    virtual size_t getH() override;
	virtual size_t getW() override;

    virtual uint32_t getPixel(size_t x, size_t y)             override;
    virtual void setPixel(size_t x, size_t y, uint32_t color) override;

private:
	int m_width  = 0;
	int m_height = 0;

	SDL_Surface* m_realSurface = nullptr;
};

class Texture
{
public:
	Texture(const Surface& pixmap);
	Texture(const std::string& img);
	Texture(const std::string& text, int size,
	        const Color& color = {0, 0, 0, 0}, 
	        const std::string& fontName = "fonts/NotoSans-Regular.ttf");
	~Texture();

	Texture& operator=(const Texture& other) = delete;
	Texture(const Texture& other)            = delete;

	Texture(Texture&& temp);
	Texture& operator=(Texture&& temp);

	const Rect& getBounds() const;
	SDL_Texture* getRealTexture() const;

private:
	SDL_Texture* m_realTexture = nullptr;
	Rect m_bounds = {0, 0, 0, 0};
};

#endif // TEXTURE_HPP
