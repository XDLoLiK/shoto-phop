#include "top_menu.hpp"
#include "app.hpp"

TopMenu::TopMenu(Widget* parent):
	Frame(parent)
{

}

TopMenu::TopMenu(const Rect& bounds, Widget* parent):
	Frame(bounds, parent)
{

}

TopMenu::~TopMenu()
{

}

void TopMenu::addChild(Widget* child)
{
	if (!m_latestChild) {
		m_latestChild = child;
		return;
	}

	auto prevBounds = m_latestChild->getBounds();
	auto curBounds  = child->getBounds();

	child->setGeometry(prevBounds.x + prevBounds.w, curBounds.y);

	m_children.push_back(child);
	m_latestChild = child;
}

void TopMenu::draw()
{
	if (m_isHidden || !this->getChildCount())
		return;

	drawSkin (m_bounds);
	drawFrame(m_bounds);

	m_childrenManager.callOnTick(getApp()->getTime());
}
