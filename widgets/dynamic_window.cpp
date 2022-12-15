#include "dynamic_window.hpp"
#include "app.hpp"

DynamicWindow::DynamicWindow(const Rect& bounds, Widget* parent):
	ContainerWidget(bounds, parent)
{
	m_bounds.w = std::max(MIN_WIN_WIDTH,  m_bounds.w);
	m_bounds.h = std::max(MIN_WIN_HEIGHT, m_bounds.h);
	int menuHeight = 20;
	m_topMenu = new Frame(Rect(0, -menuHeight, m_bounds.w, menuHeight), this);
	m_topMenu->setHidden(false);

	int buttonWidth = menuHeight;
	int buttonX = m_bounds.w - buttonWidth;
	m_closeButton = new Button("", Rect(buttonX, -menuHeight, buttonWidth, menuHeight), this);

	m_closeButton->setDefaultTexture("./skins/red_cross.png");
	m_closeButton->setHoverTexture("./skins/red_cross.png");
	m_closeButton->setFrameDefaultColor(backgroundGrey);
	m_closeButton->setFrameHoverColor(backgroundGrey);
	m_closeButton->setHidden(false);

	m_bounds.y += menuHeight;
	this->setBackground(white);
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
}

void DynamicWindow::draw()
{
	if (m_isHidden)
		return;

	drawSkin (this->getRealBounds());
	drawFrame(this->getRealBounds());
}

bool DynamicWindow::intersects(const Vec2& point)
{
	const Rect& bounds = this->getRealBounds();

	if (point.getX() < bounds.x || 
		point.getX() > bounds.x + bounds.w)
	{
		return false;
	}

	if (point.getY() < bounds.y || 
		point.getY() > bounds.y + bounds.h)
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

void DynamicWindow::setSizes(const std::pair<size_t, size_t>& sizes)
{
	int menuHeight = 20;

	m_bounds.w = std::max(static_cast<int>(sizes.first),  MIN_WIN_WIDTH);
	m_bounds.h = std::max(static_cast<int>(sizes.second), MIN_WIN_HEIGHT);
	m_topMenu->setGeometry(0, -menuHeight, m_bounds.w, menuHeight);

	int buttonWidth = menuHeight;
	int buttonX = m_bounds.w - buttonWidth;
	m_closeButton->setGeometry(buttonX, -menuHeight, buttonWidth, menuHeight);
}

bool DynamicWindow::onMouseMove(const Vec2& point, const Vec2& motion)
{
	static bool instersected = false;

	if (m_isHidden) {
		return false;
	}

	bool res = false;
	if ((m_topMenu->intersects(point) || instersected) && m_btnPressed) {
		int xShift = static_cast<int>(motion.getX());
		int yShift = static_cast<int>(motion.getY());

		this->setGeometry(m_bounds.x + xShift, m_bounds.y + yShift);

		res = true;
		instersected = true;
	}
	else {
		instersected = false;
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

	if (m_topMenu->intersects(point) && button == SDL_BUTTON_LEFT) {
		m_btnPressed = true;
		return true;
	}

	bool res = m_childrenManager.callOnButtonClick(button, point);
	if (res) {
		return res;
	}

	return false;

}

bool DynamicWindow::onButtonRelease(MouseButton button, const Vec2& point)
{
	if (m_isHidden) {
		return false;
	}

	bool res = false;
	if (button == SDL_BUTTON_LEFT) {
		m_btnPressed = false;
		res = true;
	}

	return m_childrenManager.callOnButtonRelease(button, point);
}

bool DynamicWindow::onKeyPress(Key key)
{
	if (m_isHidden) {
		return false;
	}

	if (key == SDLK_ESCAPE) {
		this->hide();
		return true;
	}

	return m_childrenManager.callOnKeyPress(key);
}

bool DynamicWindow::onKeyRelease(Key key)
{
	if (m_isHidden) {
		return false;
	}

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
