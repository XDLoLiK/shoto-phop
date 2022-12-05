#include "dynamic_window.hpp"
#include "app.hpp"

DynamicWindow::DynamicWindow(const Rect& bounds, Widget* parent):
	ContainerWidget(bounds, parent)
{
	this->setBackground(white);

	m_bounds.h     = std::max(20, m_bounds.h);
	int menuHeight = std::max(20, m_bounds.h / 40);
	m_topMenu = new Frame(Rect(0, -menuHeight, m_bounds.w, menuHeight), this);
	m_topMenu->setHidden(false);

	int buttonWidth = menuHeight;
	int buttonX     = m_bounds.w - buttonWidth;
	m_closeButton = new Button("", Rect(buttonX, -menuHeight, buttonWidth, menuHeight), this);

	m_closeButton->setDefaultTexture("./skins/red_cross.png");
	m_closeButton->setHoverTexture("./skins/red_cross.png");

	m_closeButton->setFrameDefaultColor(backgroundGrey);
	m_closeButton->setFrameHoverColor(backgroundGrey);

	m_closeButton->setHidden(false);
}

DynamicWindow::~DynamicWindow()
{
	delete m_topMenu;
	delete m_closeButton;

	m_topMenu     = nullptr;
	m_closeButton = nullptr;
}

void DynamicWindow::show()
{
	EventManager* manager = getEventManager();
	*manager += this;
	m_isHidden = false;

	for (size_t i = 0; i < m_children.size(); i++) {
		m_children[i]->setHidden(false);
	}
}

void DynamicWindow::draw()
{
	if (m_isHidden)
		return;

	drawSkin (m_bounds);
	drawFrame(m_bounds);
}

bool DynamicWindow::intersects(const Vec2& point)
{
	if (point.getX() < m_bounds.x || 
		point.getX() > m_bounds.x + m_bounds.w)
	{
		return false;
	}

	if (point.getY() < m_bounds.y || 
		point.getY() > m_bounds.y + m_bounds.h)
	{
		return false;
	}

	return true;
}

void DynamicWindow::shiftChildren(int xShift, int yShift)
{
	int thisX = m_bounds.x;
	int thisY = m_bounds.y;

	for (size_t i = 0; i < this->getChildCount(); i++) {
		Widget* cur = this->getChild(i);

		int relX = (cur->getBounds().x - thisX) + xShift;
		int relY = (cur->getBounds().y - thisY) + yShift;

		cur->setGeometry(relX, relY);
	}
}

bool DynamicWindow::onMouseMove(const Vec2& point, const Vec2& motion)
{
	if (m_isHidden) {
		return false;
	}

	bool res = false;
	if (m_topMenu->intersects(point) && m_btnPressed) {
		int xShift = static_cast<int>(motion.getX());
		int yShift = static_cast<int>(motion.getY());

		this->shiftChildren(xShift, yShift);
		this->setGeometry(m_bounds.x + xShift, m_bounds.y + yShift);

		res = true;
	}

	return res & m_childrenManager.callOnMouseMove(point, motion);
}

bool DynamicWindow::onButtonClick(MouseButton button, const Vec2& point)
{
	if (m_isHidden) {
		return false;
	}

	if (m_closeButton->intersects(point)) {
		this->hide();
		return true;
	}

	bool res = false;
	if (m_topMenu->intersects(point) && button == SDL_BUTTON_LEFT) {
		m_btnPressed = true;
		res = true;
	}

	return res & m_childrenManager.callOnButtonClick(button, point);

}

bool DynamicWindow::onButtonRelease(MouseButton button, const Vec2& point)
{
	bool res = false;
	if (button == SDL_BUTTON_LEFT) {
		m_btnPressed = false;
		res = true;
	}

	return m_childrenManager.callOnButtonRelease(button, point);
}

bool DynamicWindow::onKeyPress(Key key)
{
	return m_childrenManager.callOnKeyPress(key);
}

bool DynamicWindow::onKeyRelease(Key key)
{
	return m_childrenManager.callOnKeyRelease(key);
}

bool DynamicWindow::onTick(Time time)
{
	if (m_isHidden)
		return false;

	this->draw();
	m_childrenManager.callOnTick(time);

	return true;
}
