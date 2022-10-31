#ifndef WIDGET_HPP
#define WIDGET_HPP

#include "gvec.hpp"
#include "rect.hpp"

#include "event_manager.hpp"
#include "texture_manager.hpp"

class Widget
{
public:
	Widget(Widget* parent = nullptr);
	virtual ~Widget();

	Widget& operator=(const Widget& other) = delete;
	Widget(const Widget& other)            = delete;

	void* operator new(size_t size);
	void  operator delete(void* memptr);
	void* operator new [](size_t size);
	void  operator delete [](void* memptr);

	void show();

	void setGeometry(const Rect& bounds);
	void setGeometry(int x, int y, int w, int h);

	bool isHidden() const;
	void setHidden(bool val);

	bool isHolded() const;
	void setHolded(bool val);

	const Texture* getTexture() const;
	void setTexture(const std::string& name);

	const Rect& getBounds() const;

public:
	virtual void draw()                        = 0;
	virtual bool intersects(const Vec2& point) = 0;

	virtual void addChild   (Widget* child)    = 0;
	virtual void removeChild(Widget* child)    = 0;

	virtual size_t getChildCount()             = 0;
	virtual Widget* getChild(size_t pos)       = 0;
	virtual Widget* getParent()                = 0;

	virtual void onMouseMove(const Vec2& point, const Vec2& motion)     = 0;
	virtual void onButtonClick  (MouseButton button, const Vec2& point) = 0;
	virtual void onButtonRelease(MouseButton button, const Vec2& point) = 0;

	virtual void onKeyPress  (Key key) = 0;
	virtual void onKeyRelease(Key key) = 0;
	virtual void onTick(Time time)     = 0;

protected:
	Widget* m_parent = nullptr;
	bool m_isHidden  = true;
	bool m_isHolded  = false;

	Rect m_bounds = Rect(0, 0, 0, 0);
	const Texture* m_texture = nullptr;
};

class ContainerWidget : public Widget
{
public:
	ContainerWidget(Widget* parent = nullptr);
	virtual ~ContainerWidget();

	virtual void addChild   (Widget* child)    override;
	virtual void removeChild(Widget* child)    override;

	virtual size_t getChildCount()             override;
	virtual Widget* getChild(size_t pos)       override;
	virtual Widget* getParent()                override;

protected:
	ChildrenManager m_childrenManager = ChildrenManager();
	std::vector<Widget*> m_children = {};
};

#endif // WIDGET_HPP
