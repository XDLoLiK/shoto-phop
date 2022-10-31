#include "app.hpp"
#include "button.hpp"

extern App* __theApp__;

class CloseButton : public Button
{
public:
	CloseButton(const std::string& name = "", Widget* parent = nullptr):
		Button(name, parent)
	{

	}

	~CloseButton()
	{

	}

	virtual void onButtonClick(MouseButton button, const Vec2& point) override
	{
		if (this->intersects(point) && button == SDL_BUTTON_LEFT)
			__theApp__->close();
	}
};
