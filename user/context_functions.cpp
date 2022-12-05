#include "main.hpp"

void showWin(DynamicWindow* win)
{
	win->show();
}

void pickColor(ColorPicker* picker)
{
	booba::APPCONTEXT->fgColor = picker->getColor().mapRGBA();
}

void closeApp(App* app)
{
	app->close();
}
