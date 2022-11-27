#include "skinnable.hpp"
#include "app.hpp"

extern App*         __theApp__;
extern SkinManager* __theSkinManager__;


Skinnable::Skinnable()
{

}

Skinnable::~Skinnable()
{
	if (m_toDelete && m_hasSkin) {
		delete m_skin;
	}

	m_skin = nullptr;
}

void Skinnable::setBackground(const Color& color)
{
	if (m_toDelete && m_hasSkin)
		delete m_skin;
	
	Surface surface(SURFACE_SIZE_MIN, SURFACE_SIZE_MIN);
	surface.fillColor(color);

	m_skin = new Texture(surface);
	if (m_skin) {
		m_hasSkin  = true;
		m_toDelete = true;
	}
}

void Skinnable::setBackground(const std::string& name)
{
	if (m_toDelete && m_hasSkin)
		delete m_skin;

	SkinManager* skm = __theSkinManager__;

	const Texture* skin = skm->getSkinByName(name);
	if (!skin) skin = skm->loadSkin(name);

	m_skin = skin;
	if (m_skin) {
		m_hasSkin  = true;
		m_toDelete = false;
	}
}

void Skinnable::setBackground(const Texture* texture)
{
	if (m_toDelete && m_hasSkin)
		delete m_skin;

	m_skin = texture;
	m_hasSkin  = true;
	m_toDelete = false;
}

void Skinnable::drawSkin(const Rect& bounds)
{
	Renderer* renderer = __theApp__->getRenderer();

	if (m_hasSkin)
		renderer->copyTexture(m_skin, bounds, m_skin->getBounds());
}
