#include "main.hpp"

int main()
{
	App app("ShotoPhop");

	Frame mainFrame({0, 0, 1920, 1080});
	mainFrame.setBackground("./skins/bg.png");
	mainFrame.show();

	Canvas canvas({400, 140, 1220, 820});
	canvas.show();

	Toolbar* toolbar = new Toolbar({0, 52, 60, 1080 - 52});
	toolbar->addTools(PluginManager::getPluginManager()->getTools());
	toolbar->show();

	Frame menuFrame({0, 0, 1920, 52});
	menuFrame.setBackground(Color(251, 224, 243, 140));
	menuFrame.setFrameColor(Color(251, 224, 243, 140));
	menuFrame.show();

	ContextButton<App> closeButton("Exit", {0, 0, 100, 52});
	closeButton.setContext(&app);
	closeButton.setAction(closeApp);
	closeButton.setFrameColorDefault(Color(231, 178, 212, 255));
	closeButton.setFrameColorHover(Color(185, 130, 183, 255));
	closeButton.setBackgroundDefault(Color(231, 178, 212, 255));
	closeButton.setBackgroundHover(Color(185, 130, 183, 255));
	closeButton.show();

	DropList fileList("File", {100, 0, 100, 52});
	fileList.show();

	Button saveButton("Save", {0, 0, 360, 52});
	saveButton.buttonClick += METHOD(canvas, Canvas::save);
	fileList.addEntry(&saveButton);

	Button saveAsButton("Save As", {0, 0, 360, 52});
	saveAsButton.buttonClick += METHOD(canvas, Canvas::saveAs);
	fileList.addEntry(&saveAsButton);

	Button openButton("Open", {0, 0, 360, 52});
	openButton.buttonClick += METHOD(canvas, Canvas::open);
	fileList.addEntry(&openButton);

	DynamicWindow* colorChoiseWin = new DynamicWindow({100, 100, 600, 400});
	colorChoiseWin->setBackground(white);
	ColorPicker colorPicker({0, 0, 400, 400}, colorChoiseWin);

	ContextButton<ColorPicker> colorChooseButton("Choose", {410, 140, 180, 60}, colorChoiseWin);
	colorChooseButton.setContext(&colorPicker);
	colorChooseButton.setAction(pickForgroundColor);
	colorChooseButton.setBackgroundDefault(Color(251, 224, 243, 140));
	colorChooseButton.setBackgroundHover(Color(251, 224, 243, 140));

	ContextButton<DynamicWindow> colorButton("Color", {200, 0, 100, 52});
	colorButton.setContext(colorChoiseWin);
	colorButton.setAction(showWin);
	colorButton.show();

	ContextButton<DynamicWindow>* toolButton = new ContextButton<DynamicWindow>("Tool", {300, 0, 100, 52});
	toolButton->setContext(PluginManager::getPluginManager()->getCanvas());
	toolButton->setAction(showCanvas);
	toolButton->show();

	return app.run();
}
