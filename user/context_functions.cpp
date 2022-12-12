#include "main.hpp"

void showWin(DynamicWindow* win)
{
	win->show();

	for (size_t i = 0; i < win->getChildCount(); i++) {
		win->getChild(i)->setHidden(false);
	}
}

void showCanvas(DynamicWindow* win)
{
	win->show();

	booba::Tool* curTool = ToolManager::getToolManager()->getCurTool();
	const std::pair<size_t, size_t>* sizes = PluginManager::getPluginManager()->getToolSize(curTool);

	if (sizes != nullptr) {
		win->setSizes(*sizes);
	}
}

void pickForgroundColor(ColorPicker* picker)
{
	booba::APPCONTEXT->fgColor = picker->getColor().mapRGBA();
}

void pickBackroundColor(ColorPicker* picker)
{
	booba::APPCONTEXT->bgColor = picker->getColor().mapRGBA();
}

void closeApp(App* app)
{
	app->close();
}
