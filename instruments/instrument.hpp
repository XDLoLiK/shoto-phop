#ifndef INSTRUMENT_HPP
#define INSTRUMENT_HPP

#include "frame.hpp"
#include "plugin.hpp"

class Instrument : public booba::Tool
{
public:
	Instrument(const std::string& icon = nullptr, int x = 0, int y = 0);
	virtual ~Instrument();

	Instrument& operator=(Instrument&) = delete;
	Instrument(Instrument&)            = delete;

	virtual bool apply(Surface* surface, booba::Event* event) = 0;
	virtual bool mouseLeave(Surface* surface, booba::Event* event);

	virtual bool isSelected(MouseButton button, const Vec2& point);
	virtual void select();
	virtual void deselect();

	virtual void drawIcon  (Time time);
	virtual void drawCursor(Time time);

	virtual void setIconPos(int x, int y, int w = 40, int h = 40);
	virtual void setIconPos(const Rect& bounds);

public: /* compatability */
	virtual void apply(booba::Image*, const booba::Event*) = 0;
	virtual const char* getTexture() = 0;
	virtual void buildSetupWidget()  = 0;

protected:
	Frame* m_icon = nullptr;
};

#endif // INSTRUMENT_HPP
