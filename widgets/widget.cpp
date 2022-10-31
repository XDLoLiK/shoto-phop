#include "app.hpp"
#include "widget.hpp"


extern App* __theApp__;

std::vector<Widget*> __heapWidgets__      = std::vector<Widget*>(0);
std::vector<Widget*> __heapWidgetArrays__ = std::vector<Widget*>(0);


Widget::Widget(Widget* parent):
	m_parent(parent)
{
	if (m_parent)
		m_parent->addChild(this);

	m_isHidden = false;
}

Widget::~Widget()
{
	m_parent = nullptr;
	m_bounds = Rect(0, 0, 0, 0);
}

void Widget::show()
{
	__theApp__->eventManager += this;
}

void Widget::setGeometry(const Rect& bounds)
{
	m_bounds = bounds;
	Widget* curWid = m_parent;

	while (curWid) {
		m_bounds.x += curWid->m_bounds.x;
		m_bounds.y += curWid->m_bounds.y;
		curWid = curWid->m_parent;
	}
}

void Widget::setGeometry(int x, int y, int w, int h)
{
	m_bounds = {x, y, w, h};
	Widget* curWid = m_parent;

	while (curWid) {
		m_bounds.x += curWid->m_bounds.x;
		m_bounds.y += curWid->m_bounds.y;
		curWid = curWid->m_parent;
	}
}

bool Widget::isHidden() const
{
	return m_isHidden;
}

void Widget::setHidden(bool val)
{
	m_isHidden = val;
}

bool Widget::isHolded() const
{
	return m_isHolded;
}

void Widget::setHolded(bool val)
{
	m_isHolded = val;
}

const Texture* Widget::getTexture() const
{
	return m_texture;
}

void Widget::setTexture(const std::string& name)
{
	TextureManager* textureManager = &__theApp__->textureManager;
	const Texture* foundTexture = textureManager->getTexture(name);

	if (!foundTexture) {
		textureManager->loadTexture(name);
		foundTexture = textureManager->getTexture(name);
	}

	m_texture = foundTexture;
}

const Rect& Widget::getBounds() const
{
	return m_bounds;
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
	__heapWidgetArrays__.push_back(reinterpret_cast<Widget*>(mem + 8));

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
	Widget* wid = reinterpret_cast<Widget*>(mem + 8);

	auto begin = __heapWidgetArrays__.begin();
	auto end   = __heapWidgetArrays__.end();
	
	__heapWidgetArrays__.erase(std::remove(begin, end, wid), end);

	free(mem);
}

ContainerWidget::ContainerWidget(Widget* parent):
	Widget(parent)
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
	m_children.size();
}

Widget* ContainerWidget::getChild(size_t pos)
{
	return m_children.at(pos);
}

Widget* ContainerWidget::getParent()
{
	return m_parent;
}
