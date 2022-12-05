#include "app.hpp"
#include "texture.hpp"


extern App* __theApp__;


Surface::Surface(SDL_Surface* realSurface):
	m_realSurface(realSurface)
{
	if (m_realSurface) {
		m_width  = m_realSurface->w;
		m_height = m_realSurface->h;
	}
	else {
		std::cout << "Can't create surface from nullptr"  << std::endl;
	}
}

Surface::Surface(int width, int height):
	m_width(width),
	m_height(height)
{

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    Uint32 rmask = 0xff000000;
    Uint32 gmask = 0x00ff0000;
    Uint32 bmask = 0x0000ff00;
    Uint32 amask = 0x000000ff;
#else
    Uint32 rmask = 0x000000ff;
    Uint32 gmask = 0x0000ff00;
    Uint32 bmask = 0x00ff0000;
    Uint32 amask = 0xff000000;
#endif

	m_realSurface = SDL_CreateRGBSurface(0, width, height, 32, 
		                                    rmask, gmask, bmask, amask);
	if (!m_realSurface)
		std::cout << SDL_GetError() << std::endl;
}

Surface::Surface(const std::string& image)
{
	m_realSurface = IMG_Load(image.c_str());
	m_width  = m_realSurface->w;
	m_height = m_realSurface->h;
}

Surface::~Surface()
{
	SDL_FreeSurface(m_realSurface);
	m_realSurface = nullptr;
}

Surface::Surface(Surface&& temp)
{
	this->m_realSurface = temp.m_realSurface;
	temp.m_realSurface  = nullptr;

	m_width  = temp.m_width;
	m_height = temp.m_height;
}

Surface& Surface::operator=(Surface&& temp)
{
	SDL_FreeSurface(this->m_realSurface);

	this->m_realSurface = temp.m_realSurface;
	temp.m_realSurface  = nullptr;

	m_width  = temp.m_width;
	m_height = temp.m_height;

	return *this;
}

int Surface::getWidth() const
{
	return m_width;
}

int Surface::getHeight() const
{
	return m_height;
}

Color* Surface::getPixmap(int* width, int* height)
{
	if (width)  *width  = m_width;
	if (height) *height = m_height;

	return reinterpret_cast<Color*>(m_realSurface->pixels);
}

void Surface::fillColor(const Color& color)
{
	SDL_PixelFormat* format = m_realSurface->format;
	SDL_FillRect(m_realSurface, NULL, SDL_MapRGBA(format, color.r, color.g,
		                                                  color.b, color.a));
}


SDL_Surface* Surface::getRealSurface() const
{
	return m_realSurface;
}

Texture::Texture(const Surface& pixmap)
{
	SDL_Surface*  realSurface  = pixmap.getRealSurface(); 
	SDL_Renderer* realRenderer = __theApp__->getRenderer()->getRealRenderer();

	m_realTexture = SDL_CreateTextureFromSurface(realRenderer, realSurface);
	m_bounds = {0, 0, pixmap.getWidth(), pixmap.getHeight()};
}

Texture::Texture(const std::string& img)
{
	SDL_Surface* image = IMG_Load(img.c_str());
	if (!image)
		std::cout << IMG_GetError() << std::endl;

	SDL_Renderer* realRenderer = __theApp__->getRenderer()->getRealRenderer();

	m_realTexture = SDL_CreateTextureFromSurface(realRenderer, image);
	m_bounds = {0, 0, image->w, image->h};

	SDL_FreeSurface(image);
}

Texture::Texture(const std::string& text, int size,
                 const Color& color, const std::string& fontName)
{
	TTF_Font* font = TTF_OpenFont(fontName.c_str(), size);
	int curSize  = size;
	int realSize = 0;
	TTF_SizeText(font, text.c_str(), NULL, &realSize);

	while (realSize > size) {
		TTF_CloseFont(font);
		curSize--;
		font = TTF_OpenFont(fontName.c_str(), curSize);
		TTF_SizeText(font, text.c_str(), NULL, &realSize);
	}

	SDL_Color realColor = {color.r, color.g, color.b, color.a};
	SDL_Surface* message = TTF_RenderText_Blended(font, text.c_str(), realColor); 

	SDL_Renderer* realRenderer = __theApp__->getRenderer()->getRealRenderer();

	m_realTexture = SDL_CreateTextureFromSurface(realRenderer, message);
	m_bounds = {0, 0, message->w, message->h};

	TTF_CloseFont(font);
	SDL_FreeSurface(message);
}

Texture::~Texture()
{
	SDL_DestroyTexture(m_realTexture);
	m_realTexture = nullptr;
}

Texture::Texture(Texture&& temp)
{
	this->m_realTexture = temp.m_realTexture;
	this->m_bounds      = temp.m_bounds;

	temp.m_realTexture = nullptr;
}

Texture& Texture::operator=(Texture&& temp)
{
	SDL_DestroyTexture(m_realTexture);

	this->m_realTexture = temp.m_realTexture;
	this->m_bounds      = temp.m_bounds;

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
