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

	void setBackground(const Color& color);
	void setBackground(const std::string& name);
	void setBackground(const Texture* texture);

protected:
	void drawSkin(const Rect& bounds);

private:
	bool m_hasSkin  = false;
	bool m_toDelete = false;

	const Texture* m_skin = nullptr;
};

#endif // SKINABLE_HPP
