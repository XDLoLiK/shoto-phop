#include "hoverable.hpp"
#include "app.hpp"

Hoverable::Hoverable()
{

}

Hoverable::~Hoverable()
{
	delete m_hoverTexture;
	delete m_defaultTexture;

	m_hoverTexture   = nullptr;
	m_defaultTexture = nullptr;
}

void Hoverable::setHoverTexture(const Color& color)
{
	Surface surface(SURFACE_SIZE_MIN, SURFACE_SIZE_MIN);
	surface.fillColor(color);

	delete m_hoverTexture;
	m_hoverTexture = new Texture(surface);
}

void Hoverable::setHoverTexture(const std::string& name)
{
	delete m_hoverTexture;
	m_hoverTexture = new Texture(name);
}

void Hoverable::setDefaultTexture(const Color& color)
{
	Surface surface(SURFACE_SIZE_MIN, SURFACE_SIZE_MIN);
	surface.fillColor(color);

	delete m_defaultTexture;
	m_defaultTexture = new Texture(surface);
}

void Hoverable::setDefaultTexture(const std::string& name)
{
	delete m_defaultTexture;
	m_defaultTexture = new Texture(name);
}

