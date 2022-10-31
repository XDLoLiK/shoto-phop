#ifndef MENU_BUTTONS_HPP
#define MENU_BUTTONS_HPP

#include "frame.hpp"
#include "button.hpp"

class DropList : public Frame
{
public:
	DropList(const std::string& name = "", Widget* parent = nullptr):
		Frame(parent),
		m_name(name)
	{

	}

	~DropList()
	{

	}

	virtual void onMouseMove(const Vec2& point, const Vec2& motion) override
	{
		if (this->intersects(point) || this->hoversChildren(point)) {
			for (size_t i = 0; i < m_children.size(); i++)
				m_children[i]->setHidden(false);
		}
		else {
			for (size_t i = 0; i < m_children.size(); i++)
				m_children[i]->setHidden(true);
		}
	}

	bool hoversChildren(const Vec2& point)
	{
		for (size_t i = 0; i < m_children.size(); i++)
			if (m_children[i]->intersects(point) && !m_children[i]->isHidden())
				return true;

		return false;
	}

protected:
	std::string m_name = "";
};

class ChooseButton : public Button
{
public:
	ChooseButton(const std::string& name = "", Widget* parent = nullptr,
		         Widget* interactive = nullptr, const std::string& tex = ""):
		Button(name, parent),
		m_interactive(interactive),
		m_textureName(tex)
	{

	}

	~ChooseButton()
	{

	}

	virtual void onButtonClick(MouseButton button, const Vec2& point) override
	{
		if (this->intersects(point) && button == SDL_BUTTON_LEFT)
			m_interactive->setTexture(m_textureName);
	}

private:
	Widget* m_interactive = nullptr;
	std::string m_textureName = "";
};

#endif // MENU_BUTTONS_HPP
