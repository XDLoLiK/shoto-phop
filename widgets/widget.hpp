#ifndef WIDGET_HPP
#define WIDGET_HPP

#include "vec.hpp"
#include "rect.hpp"

#include "event_manager.hpp"
#include "skin_manager.hpp"

#include "modifiers/serializable.hpp"
#include "modifiers/skinnable.hpp"

class Widget
{
public:
	Widget(Widget* parent = nullptr);
	Widget(const Rect& bounds, Widget* parent = nullptr);
	virtual ~Widget();

	Widget& operator=(const Widget& other) = delete;
	Widget(const Widget& other)            = delete;

	void* operator new(size_t size);
	void  operator delete(void* memptr);

	void* operator new [](size_t size);
	void  operator delete [](void* memptr);

	virtual void show();
	virtual void hide();

	virtual bool isHidden() const;
	virtual void setHidden(bool val);

	virtual bool isHovered() const;
	virtual void setHovered(bool val);

	virtual bool isClicked() const;
	virtual void setClicked(bool val);

	virtual bool isHolded() const;
	virtual void setHolded(bool val);

	virtual bool isInFocuse() const;
	virtual void setInFocuse(bool val);

	virtual const Rect& getBounds() const;

	virtual void setGeometry(const Rect& bounds);
	virtual void setGeometry(int x, int y, int w = -1, int h = -1);

	virtual void addChild   (Widget* child);
	virtual void removeChild(Widget* child);

	virtual size_t getChildCount();
	virtual Widget* getChild(size_t pos);
	virtual Widget* getParent();
	virtual void setParent(Widget* parent);

public: /* pure virtual */
	virtual void draw()                        = 0;
	virtual bool intersects(const Vec2& point) = 0;

	virtual bool onMouseMove(const Vec2& point, const Vec2& motion)     = 0;
	virtual bool onButtonClick  (MouseButton button, const Vec2& point) = 0;
	virtual bool onButtonRelease(MouseButton button, const Vec2& point) = 0;

	virtual bool onKeyPress  (Key key) = 0;
	virtual bool onKeyRelease(Key key) = 0;
	virtual bool onTick(Time time)     = 0;

protected:
	Widget* m_parent = nullptr;

	bool m_isHidden   = true;
	bool m_isHovered  = false;
	bool m_isClicked  = false;
	bool m_isHolded   = false;
	bool m_isInFocuse = false;

	Rect m_bounds = Rect(0, 0, 0, 0);
};

class ContainerWidget : public Widget
{
public:
	ContainerWidget(Widget* parent = nullptr);
	ContainerWidget(const Rect& bounds, Widget* parent = nullptr);
	virtual ~ContainerWidget();

	virtual void addChild   (Widget* child)    override;
	virtual void removeChild(Widget* child)    override;

	virtual size_t getChildCount()             override;
	virtual Widget* getChild(size_t pos)       override;

protected:
	ChildrenManager m_childrenManager = ChildrenManager();
	std::vector<Widget*> m_children = {};
};

class ModalWidget : public Widget
{
public:
	ModalWidget(Widget* parent = nullptr);
	ModalWidget(const Rect& bounds, Widget* parent = nullptr);
	virtual ~ModalWidget();

	ModalWidget& operator=(ModalWidget& other) = delete;
	ModalWidget(ModalWidget& other)            = delete;

	virtual void addChild   (Widget* child)    override;
	virtual void removeChild(Widget* child)    override;

	virtual size_t getChildCount()             override;
	virtual Widget* getChild(size_t pos)       override;

protected:
	ChildrenManager m_childrenManager = ChildrenManager();
	EventManager*   m_eventManager    = nullptr;

	std::vector<Widget*> m_children = {};
};

#endif // WIDGET_HPP
