#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <cstring>
#include <deque>

#include "widget.hpp"
#include "context_button.hpp"
#include "instrument.hpp"
#include "tool_manager.hpp"
#include "scrollbar.hpp"
#include "dir.hpp"

#include "modifiers/framable.hpp"

class HistoryBuffer
{
public:
	HistoryBuffer(size_t size)
	{
		m_statesNumber = size;
		m_states.resize(m_statesNumber);
	}

	~HistoryBuffer()
	{
		for (int i = 0; i < m_statesNumber; i++) {
			freePos(i);
		}

		m_states.clear();
		m_states.shrink_to_fit();
	}

	void initBuffer(Surface* initSurf)
	{
		static bool wasCalled = false;
		if (wasCalled) {
			return;
		} else {
			wasCalled = true;
			m_head = m_tail = m_cur = 0;
		}

		size_t w = initSurf->getWidth();
		size_t h = initSurf->getHeight();
		size_t pixelsNumber = static_cast<size_t>(w * h);
		size_t sizeofPixel  = sizeof(Color);

		Color* initState = new Color[pixelsNumber];
		memcpy(initState, initSurf->getPixmap(), pixelsNumber * sizeofPixel);
		m_states[m_cur] = initState;
	}

	void addState(Surface* newSurf)
	{
		if (incIndex(m_cur) == m_head) {
			freePos(m_head);
			m_head = incIndex(m_head);
			m_tail = incIndex(m_cur);
		} else {
			m_tail = incIndex(m_cur);
		}

		size_t w = newSurf->getWidth();
		size_t h = newSurf->getHeight();
		size_t pixelsNumber = static_cast<size_t>(w * h);
		size_t sizeofPixel  = sizeof(Color);

		m_cur = incIndex(m_cur);
		Color* newState = new Color[pixelsNumber];
		memcpy(newState, newSurf->getPixmap(), pixelsNumber * sizeofPixel);
		m_states[m_cur] = newState;
	}

	void nextState(Surface* destSurf)
	{
		if (m_cur == m_tail) {
			return;
		}

		size_t w = destSurf->getWidth();
		size_t h = destSurf->getHeight();
		size_t pixelsNumber = static_cast<size_t>(w * h);
		size_t sizeofPixel  = sizeof(Color);

		m_cur = incIndex(m_cur);
		Color* nextState = m_states[m_cur];
		memcpy(destSurf->getPixmap(), nextState, pixelsNumber * sizeofPixel);
	}

	void prevState(Surface* destSurf)
	{
		if (m_cur == m_head) {
			return;
		}

		size_t w = destSurf->getWidth();
		size_t h = destSurf->getHeight();
		size_t pixelsNumber = static_cast<size_t>(w * h);
		size_t sizeofPixel  = sizeof(Color);

		m_cur = decIndex(m_cur);
		Color* prevState = m_states[m_cur];
		memcpy(destSurf->getPixmap(), prevState, pixelsNumber * sizeofPixel);
	}

private:
	inline void freePos(size_t idx)
	{
		delete [] m_states[idx];
		m_states[idx] = nullptr;
	}

	inline size_t incIndex(size_t idx)
	{
		return (idx + 1 >= m_statesNumber) ? 0 : idx + 1;
	}

	inline size_t decIndex(size_t idx)
	{
		return (idx > 0) ? idx - 1 : m_statesNumber - 1;
	}

private:
	size_t m_statesNumber = 0;
	size_t m_cur  = 0;
	size_t m_head = 0;
	size_t m_tail = 0;
	std::vector<Color*> m_states = {};
};

class Canvas;

class Layer
{
public:
	Layer(Canvas* canvas = nullptr)
	{
		m_surface       = new Surface(1920, 1080);
		m_historyBuffer = new HistoryBuffer(32);
		m_chooseButton  = new ContextButton<Canvas>();
	}

	~Layer()
	{
		delete m_surface;
		delete m_historyBuffer;
		delete m_chooseButton;
	}

	Layer(Layer& other)            = delete;
	Layer& operator=(Layer& other) = delete;

private:
	Surface* m_surface                    = nullptr;
	HistoryBuffer* m_historyBuffer        = nullptr;
	ContextButton<Canvas>* m_chooseButton = nullptr;
};

class Canvas : public ContainerWidget, public Framable
{
public:
	Canvas(const Rect& bounds = {0, 0, 0, 0}, Widget* parent = nullptr);
	virtual ~Canvas();

	Canvas& operator=(Canvas&) = delete;
	Canvas(Canvas&)            = delete;

	void save();
	void saveAs();
	void open();

public:
	virtual void draw()                        override;
	virtual bool intersects(const Vec2& point) override;

	virtual bool onMouseMove(const Vec2& point, const Vec2& motion)     override;
	virtual bool onButtonClick  (MouseButton button, const Vec2& point) override;
	virtual bool onButtonRelease(MouseButton button, const Vec2& point) override;

	virtual bool onKeyPress  (Key key) override;
	virtual bool onKeyRelease(Key key) override;
	virtual bool onTick(Time time)     override;

private:
	std::vector<Surface*> m_layers = {};
	Surface* m_drawingSurface = nullptr;
	HistoryBuffer m_historyBuffer = HistoryBuffer(32);

	/* Cancel actions */
	bool m_ctrlPressed = false;

	/* Periphery */
	Frame*      m_cornerSquare  = nullptr;
	HScrollbar* m_horizontalBar = nullptr;
	VScrollbar* m_verticalBar   = nullptr;
	Rect m_copyBounds = {0, 0, 0, 0};

	/* Save options */
	std::string m_curFile = "";
	const Key m_saveKey   = SDLK_s;
	const Key m_saveAsKey = SDLK_a;
	const Key m_openKey   = SDLK_o;
};

#endif // CANVAS_HPP
