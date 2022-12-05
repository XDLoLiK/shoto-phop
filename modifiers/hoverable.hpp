#ifndef HOVERABLE_HPP
#define HOVERABLE_HPP

#include "texture.hpp"

class Hoverable
{
public:
	Hoverable();
	virtual ~Hoverable();

	Hoverable& operator=(const Hoverable& other) = delete;
	Hoverable(const Hoverable& other)            = delete;

	void setHoverTexture(const Color& color);
	void setHoverTexture(const std::string& name);
	void setDefaultTexture(const Color& color);
	void setDefaultTexture(const std::string& name);

protected:
	Texture* m_hoverTexture   = nullptr;
	Texture* m_defaultTexture = nullptr;
};

#endif // HOVERABLE_HPP
