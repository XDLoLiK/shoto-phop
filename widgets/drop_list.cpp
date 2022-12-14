#include "drop_list.hpp"
#include "button.hpp"
#include "app.hpp"


extern App* __theApp__;


DropList::DropList(const std::string& text, int size, Widget* parent):
	ContainerWidget(parent)
{
	m_label = new Label(text, size, black);
	
	m_bounds.w = std::max(m_label->getBounds().w, m_bounds.w);
	m_bounds.h = std::max(m_label->getBounds().h, m_bounds.h);

	this->setFrameColor(Color(231, 178, 212, 255));
	this->setBackground(Color(231, 178, 212, 255));
}

DropList::DropList(const std::string& text, const Rect& bounds, Widget* parent):
	ContainerWidget(bounds, parent)
{
	m_label = new Label(text, m_bounds.h, black);

	m_bounds.w = std::max(m_label->getBounds().w, m_bounds.w);
	m_bounds.h = std::max(m_label->getBounds().h, m_bounds.h);
	
	this->setFrameColor(Color(231, 178, 212, 255));
	this->setBackground(Color(231, 178, 212, 255));

	m_label->setGeometry(m_bounds.x + (m_bounds.w - m_label->getBounds().w) / 2, m_bounds.y);
}

DropList::~DropList()
{
	delete m_label;
	m_label = nullptr;
}

void DropList::setShortcut(Key key)
{
	m_hasShortcut = true;
	m_shotrcut = key;
}

void DropList::setGeometry(const Rect& bounds)
{
	m_bounds = bounds;
	Widget* curWid = m_parent;

	while (curWid) {
		m_bounds.x += curWid->getBounds().x;
		m_bounds.y += curWid->getBounds().y;
		curWid = curWid->getParent();
	}

	auto oldText = m_label->getText();
	delete m_label;

	m_label = new Label(oldText, m_bounds.h, black);

	m_bounds.w = std::max(m_label->getBounds().w, m_bounds.w);
	m_bounds.h = std::max(m_label->getBounds().h, m_bounds.h);

	m_label->setGeometry(m_bounds.x + (m_bounds.w - m_label->getBounds().w) / 2, m_bounds.y);
}

void DropList::setGeometry(int x, int y, int w, int h)
{
	w = (w == -1) ? m_bounds.w : w;
	h = (h == -1) ? m_bounds.h : h;

	this->setGeometry({x, y, w, h});
}

void DropList::draw()
{
	if (m_isHidden)
		return;

	drawSkin (m_bounds);
	drawFrame(m_bounds);

	m_label->draw();
}

bool DropList::intersects(const Vec2& point)
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

void DropList::addEntry(Button* entry)
{
	this->addChild(entry);
	entry->setGeometry(0, static_cast<int>(this->getChildCount()) * m_bounds.h);
}

void DropList::addChild(Widget* child)
{
	if (!child)
		return;

	child->setParent(this);

	m_children.push_back(child);
	m_childrenManager += child;
}

void DropList::removeChild(Widget* child)
{
	auto start = std::remove(m_children.begin(), m_children.end(), child);
	auto end   = m_children.end();

	m_children.erase(start, end);

	for (size_t i = 0; i < this->getChildCount(); i++) {
		Widget* curChild = this->getChild(i);
		curChild->setGeometry(0, (static_cast<int>(i) + 1) * m_bounds.h);
	}
}

bool DropList::onMouseMove(const Vec2& point, const Vec2& motion)
{
	if (m_isHidden)
		return false;

	if (!this->intersects(point) && !this->intersectsChildren(point)) {
		if (m_shotrcutActive) {
			return false;
		}

		for (size_t i = 0; i < this->getChildCount(); i++)
			this->getChild(i)->setHidden(true);

		this->setFrameColor(Color(231, 178, 212, 255));
		this->setBackground(Color(231, 178, 212, 255));
		return false;
	}

	for (size_t i = 0; i < this->getChildCount(); i++)
		this->getChild(i)->setHidden(false);

	this->setFrameColor(Color(185, 130, 183, 255));
	this->setBackground(Color(185, 130, 183, 255));

	m_shotrcutActive = false;

	bool res = m_childrenManager.callOnMouseMove(point, motion);
	return res | true;
}

bool DropList::intersectsChildren(const Vec2& point)
{
	for (size_t i = 0; i < this->getChildCount(); i++) {
		if (this->getChild(i)->intersects(point) && !this->getChild(i)->isHidden()) {
		 	return true;
		}
	}

	return false;
}

bool DropList::onButtonClick(MouseButton button, const Vec2& point)
{
	if (m_isHidden)
		return false;

	return m_childrenManager.callOnButtonClick(button, point);
}

bool DropList::onButtonRelease(MouseButton button, const Vec2& point)
{
	if (m_isHidden)
		return false;

	return m_childrenManager.callOnButtonRelease(button, point);
}

bool DropList::onKeyPress(Key key)
{
	if (m_isHidden)
		return false;

	if (key == SDLK_LCTRL) {
		m_ctrlPresed = true;
	}

	if (m_ctrlPresed && m_hasShortcut && key == m_shotrcut) {
		for (size_t i = 0; i < this->getChildCount(); i++)
			this->getChild(i)->setHidden(false);

		this->setFrameColor(Color(185, 130, 183, 255));
		this->setBackground(Color(185, 130, 183, 255));

		m_shotrcutActive = true;
		return true;
	}

	return m_childrenManager.callOnKeyPress(key);
}

bool DropList::onKeyRelease(Key key)
{
	if (m_isHidden)
		return false;

	if (key == SDLK_LCTRL) {
		m_ctrlPresed = false;
	}

	return m_childrenManager.callOnKeyRelease(key);
}

bool DropList::onTick(Time time)
{
	if (m_isHidden)
		return false;

	this->draw();
	m_childrenManager.callOnTick(time);
	return true;
}
