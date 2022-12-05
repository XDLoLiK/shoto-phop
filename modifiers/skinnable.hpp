#ifndef SKINABLE_HPP
#define SKINABLE_HPP

#include "skin_manager.hpp"
#include "renderer.hpp"

class Skinnable
{
public:
	Skinnable();
	virtual ~Skinnable();

	Skinnable& operator=(Skinnable& other) = delete;
	Skinnable(Skinnable& other)            = delete;

	void destroyTextures();
	void destroyTextureDefault();
	void destroyTextureHover();

	void setBackground(const Color& color);
	void setBackground(const std::string& name);
	void setBackground(const Texture* texture);

	void setBackgroundDefault(const Color& color);
	void setBackgroundDefault(const std::string& name);
	void setBackgroundDefault(const Texture* texture);

	void setBackgroundHover(const Color& color);
	void setBackgroundHover(const std::string& name);
	void setBackgroundHover(const Texture* texture);

protected:
	void drawSkin(const Rect& bounds, bool isHovered = false);

private:
	bool m_bgChanged = true;

	bool m_toDeleteDefault = false;
	bool m_toDeleteHover   = false;

	const Texture* m_skinDefault = nullptr;
	const Texture* m_skinHover   = nullptr;
};

#endif // SKINABLE_HPP
