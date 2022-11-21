#ifndef LABEL_HPP
#define LABEL_HPP

#include "widget.hpp"

class Label : public Widget
{
public:
	Label(const std::string& text = "", int size = 0, const Color& color = black,
	      const std::string& font = "fonts/NotoSans-Regular.ttf", Widget* parent = nullptr);
	virtual ~Label();

	Label& operator=(Label&) = delete;
	Label(Label&)            = delete;

	const std::string getText() const;

public:
	virtual void setGeometry(const Rect& bounds)                   override;
	virtual void setGeometry(int x, int y, int w = -1, int h = -1) override;

	virtual void draw()                        override;
	virtual bool intersects(const Vec2& point) override;

	virtual void addChild   (Widget* child)    override;
	virtual void removeChild(Widget* child)    override;

	virtual size_t getChildCount()             override;
	virtual Widget* getChild(size_t pos)       override;
	virtual Widget* getParent()                override;
	virtual void setParent(Widget* parent)     override;

public:
	virtual bool onMouseMove(const Vec2& point, const Vec2& motion)     override;
	virtual bool onButtonClick  (MouseButton button, const Vec2& point) override;
	virtual bool onButtonRelease(MouseButton button, const Vec2& point) override;

	virtual bool onKeyPress  (Key key) override;
	virtual bool onKeyRelease(Key key) override;
	virtual bool onTick(Time time)     override;

protected:
	std::string m_text = "";
	const Texture* m_textTexture = nullptr;
};

#endif // LABEL_HPP
