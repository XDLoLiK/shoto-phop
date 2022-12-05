#include "skinnable.hpp"
#include "app.hpp"

static inline bool operator==(const Rect& first, const Rect& second)
{
	return (first.x == second.x && first.y == second.y &&
		    first.w == second.w && first.h == second.h);
}

Skinnable::Skinnable()
{

}

Skinnable::~Skinnable()
{
	this->destroyTextures();
}

void Skinnable::destroyTextures()
{
	this->destroyTextureDefault();
	this->destroyTextureHover();
}

void Skinnable::destroyTextureDefault()
{
	if (m_toDeleteDefault) {
		delete m_skinDefault;
	}
	m_skinDefault = nullptr;
	m_toDeleteDefault = false;
}

void Skinnable::destroyTextureHover()
{
	if (m_toDeleteHover) {
		delete m_skinHover;
	}
	m_skinHover = nullptr;
	m_toDeleteHover = false;
}

void Skinnable::setBackground(const Color& color)
{
	this->destroyTextures();
	
	Surface surface(SURFACE_SIZE_MIN, SURFACE_SIZE_MIN);
	surface.fillColor(color);

	m_skinDefault = new Texture(surface);
	m_skinHover   = new Texture(surface);

	if (m_skinDefault) {
		m_toDeleteDefault = true;
	}

	if (m_toDeleteHover) {
		m_toDeleteHover = true;
	}

	m_bgChanged = true;
}

void Skinnable::setBackground(const std::string& name)
{
	this->destroyTextures();

	SkinManager* skm = getSkinManager();
	const Texture* skin = skm->getSkinByName(name);
	if (!skin) skin = skm->loadSkin(name);
	if (!skin) return;

	m_skinDefault = skin;
	m_skinHover   = skin;

	m_bgChanged = true;
}

void Skinnable::setBackground(const Texture* texture)
{
	this->destroyTextures();

	m_skinDefault = texture;
	m_skinHover   = texture;

	m_bgChanged = true;
}

void Skinnable::setBackgroundDefault(const Color& color)
{
	this->destroyTextureDefault();
	
	Surface surface(SURFACE_SIZE_MIN, SURFACE_SIZE_MIN);
	surface.fillColor(color);

	m_skinDefault = new Texture(surface);
	if (m_skinDefault) {
		m_toDeleteDefault = true;
	}

	m_bgChanged = true;
}

void Skinnable::setBackgroundDefault(const std::string& name)
{
	this->destroyTextureDefault();

	SkinManager* skm = getSkinManager();
	const Texture* skin = skm->getSkinByName(name);
	if (!skin) skin = skm->loadSkin(name);
	if (!skin) return;

	m_skinDefault = skin;
	m_bgChanged = true;
}

void Skinnable::setBackgroundDefault(const Texture* texture)
{
	this->destroyTextureDefault();

	m_skinDefault = texture;
	m_bgChanged = true;
}

void Skinnable::setBackgroundHover(const Color& color)
{
	this->destroyTextureHover();
	
	Surface surface(SURFACE_SIZE_MIN, SURFACE_SIZE_MIN);
	surface.fillColor(color);

	m_skinHover = new Texture(surface);
	if (m_toDeleteHover) {
		m_toDeleteHover = true;
	}

	m_bgChanged = true;
}

void Skinnable::setBackgroundHover(const std::string& name)
{
	this->destroyTextureHover();

	SkinManager* skm = getSkinManager();
	const Texture* skin = skm->getSkinByName(name);
	if (!skin) skin = skm->loadSkin(name);
	if (!skin) return;

	m_skinHover = skin;
	m_bgChanged = true;
}

void Skinnable::setBackgroundHover(const Texture* texture)
{
	this->destroyTextureHover();

	m_skinHover = texture;
	m_bgChanged = true;
}

void Skinnable::drawSkin(const Rect& bounds, bool isHovered)
{
	static Rect oldBounds  = {0, 0, 0, 0};
	static bool hoverState = false;

	if (!m_bgChanged && oldBounds == bounds && isHovered == hoverState) {
		return;
	}

	Renderer* renderer = getApp()->getRenderer();

	if (m_skinDefault && !isHovered) {
		renderer->copyTexture(m_skinDefault, bounds, m_skinDefault->getBounds());
	}
	else if (m_skinHover) {
		renderer->copyTexture(m_skinHover, bounds, m_skinHover->getBounds());
	}

	oldBounds  = bounds;
	hoverState = isHovered;
	m_bgChanged = false;
}
