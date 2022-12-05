#include "app.hpp"
#include "widget.hpp"


std::vector<Widget*> __heapWidgets__      = std::vector<Widget*>(0);
std::vector<Widget*> __heapWidgetArrays__ = std::vector<Widget*>(0);


Widget::Widget(Widget* parent):
	m_parent(parent)
{
	if (m_parent) {
		m_parent->addChild(this);
		this->setGeometry(parent->getBounds());
	}
}

Widget::Widget(const Rect& bounds, Widget* parent):
	m_parent(parent),
	m_bounds(bounds)
{
	if (m_parent)
		m_parent->addChild(this);

	this->setGeometry(m_bounds);
}

Widget::~Widget()
{
	m_parent = nullptr;
	m_bounds = Rect(0, 0, 0, 0);
}

void Widget::show()
{
	EventManager* manager = getEventManager();
	*manager += this;
	m_isHidden = false;
}

void Widget::hide()
{
	EventManager* manager = getEventManager();
	*manager -= this;
	m_isHidden = true;
}

void Widget::setGeometry(const Rect& bounds)
{
	m_bounds = bounds;
	Widget* curWid = m_parent;

	while (curWid) {
		m_bounds.x += curWid->getBounds().x;
		m_bounds.y += curWid->getBounds().y;
		curWid = curWid->getParent();
	}
}

void Widget::setGeometry(int x, int y, int w, int h)
{
	w = (w == -1) ? m_bounds.w : w;
	h = (h == -1) ? m_bounds.h : h;

	this->setGeometry({x, y, w, h});
}

bool Widget::isHidden() const
{
	return m_isHidden;
}

void Widget::setHidden(bool val)
{
	m_isHidden = val;
}

bool Widget::isHovered() const
{
	return m_isHovered;
}

void Widget::setHovered(bool val)
{
	m_isHovered = val;
}

bool Widget::isHolded() const
{
	return m_isHolded;
}

void Widget::setHolded(bool val)
{
	m_isHolded = val;
}

bool Widget::isClicked() const
{
	return m_isClicked;
}

void Widget::setClicked(bool val)
{
	m_isClicked = val;
}

bool Widget::isInFocuse() const
{
	return m_isInFocuse;
}

void Widget::setInFocuse(bool val)
{
	m_isInFocuse = val;
}

const Rect& Widget::getBounds() const
{
	return m_bounds;
}

void Widget::addChild(Widget*)
{

}

void Widget::removeChild(Widget*)
{

}

size_t Widget::getChildCount()
{
	return 0;
}

Widget* Widget::getChild(size_t)
{
	return nullptr;
}

Widget* Widget::getParent()
{
	return m_parent;
}

void Widget::setParent(Widget* parent)
{
	m_parent = parent;
}

void* Widget::operator new(size_t size)
{
	void* mem = calloc(1, size);
	__heapWidgets__.push_back(static_cast<Widget*>(mem));

	return mem;
}

void* Widget::operator new [](size_t size)
{
	void* mem = calloc(1, size);
	__heapWidgetArrays__.push_back(reinterpret_cast<Widget*>((char*)mem + 8));

	return mem;
}

void Widget::operator delete(void* mem)
{
	Widget* wid = static_cast<Widget*>(mem);

	auto begin = __heapWidgets__.begin();
	auto end   = __heapWidgets__.end();
	
	__heapWidgets__.erase(std::remove(begin, end, wid), end);

	free(mem);
}

void Widget::operator delete [](void* mem)
{
	Widget* wid = reinterpret_cast<Widget*>((char*)mem + 8);

	auto begin = __heapWidgetArrays__.begin();
	auto end   = __heapWidgetArrays__.end();
	
	__heapWidgetArrays__.erase(std::remove(begin, end, wid), end);

	free(mem);
}

ContainerWidget::ContainerWidget(Widget* parent):
	Widget(parent)
{

}

ContainerWidget::ContainerWidget(const Rect& bounds, Widget* parent):
	Widget(bounds, parent)
{

}

ContainerWidget::~ContainerWidget()
{
	m_children.clear();
	m_children.shrink_to_fit();
}

void ContainerWidget::addChild(Widget* child)
{
	if (!child)
		return;

	m_children.push_back(child);
	m_childrenManager += child;
}

void ContainerWidget::removeChild(Widget* child)
{
	auto start = std::remove(m_children.begin(), m_children.end(), child);
	auto end   = m_children.end();

	m_children.erase(start, end);
}

size_t ContainerWidget::getChildCount()
{
	return m_children.size();
}

Widget* ContainerWidget::getChild(size_t pos)
{
	return m_children.at(pos);
}

ModalWidget::ModalWidget(Widget* parent):
	Widget(parent)
{
	EventManager* manager = getEventManager();
	m_eventManager = new EventManager(manager);
}

ModalWidget::ModalWidget(const Rect& bounds, Widget* parent):
	Widget(bounds, parent)
{
	EventManager* manager = getEventManager();
	m_eventManager = new EventManager(manager);
}

ModalWidget::~ModalWidget()
{
	m_children.clear();
	m_children.shrink_to_fit();

	delete m_eventManager;
	m_eventManager = nullptr;
}

void ModalWidget::addChild(Widget* child)
{
	if (!child)
		return;

	m_children.push_back(child);
	m_childrenManager += child;
}

void ModalWidget::removeChild(Widget* child)
{
	auto start = std::remove(m_children.begin(), m_children.end(), child);
	auto end   = m_children.end();

	m_children.erase(start, end);
}

size_t ModalWidget::getChildCount()
{
	return m_children.size();
}

Widget* ModalWidget::getChild(size_t pos)
{
	return m_children.at(pos);
}
