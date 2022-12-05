// #ifndef TOOLBAR_HPP
// #define TOOLBAR_HPP

// class Toolbar : public ContainerWidget
// {
// public:
// 	Toolbar(const Rect& bounds = {0, 0, 0, 0}, Widget* parent = nullptr);
// 	~Toolbar();

// 	void addTool(Tool* tool);
// 	void addTools(std::vector<Tool*> tools);

// 	void linkCanvas(Canvas* canvas);

// 	virtual void draw()                        = 0;
// 	virtual bool intersects(const Vec2& point) = 0;

// 	virtual bool onMouseMove(const Vec2& point, const Vec2& motion)     = 0;
// 	virtual bool onButtonClick  (MouseButton button, const Vec2& point) = 0;
// 	virtual bool onButtonRelease(MouseButton button, const Vec2& point) = 0;

// 	virtual bool onKeyPress  (Key key) = 0;
// 	virtual bool onKeyRelease(Key key) = 0;
// 	virtual bool onTick(Time time)     = 0;

// private:
// 	Canvas* m_linkedCanvas = nullptr;

// 	size_t m_toolsCount = 0;
// 	std::vector<ContextButton<Tool>*> m_selectors = {};
// }

// #endif // TOOLBAR_HPP
