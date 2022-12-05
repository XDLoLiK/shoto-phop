#include "main.hpp"

/* Global variable needed for plugins */
booba::ApplicationContext* booba::APPCONTEXT = nullptr;

int main()
{
	App app("ShotoPhop");

	Frame mainFrame({0, 0, 1920, 1080});
	mainFrame.setBackground("./skins/bg.png");
	mainFrame.show();

	Frame toolBox({100, 280, 380, 650});
	toolBox.setBackground(white);
	toolBox.setFrameColor(white);
	toolBox.show();

	Canvas canvas({620, 140, 1220, 820});
	canvas.show();
	canvas.addToolBox(&toolBox);

	Frame menuFrame({0, 0, 1920, 52});
	menuFrame.setBackground(Color(251, 224, 243, 140));
	menuFrame.setFrameColor(Color(251, 224, 243, 140));
	menuFrame.show();

	ContextButton<App> closeButton("Exit", {0, 0, 100, 52});
	closeButton.setContext(&app);
	closeButton.setAction(closeApp);
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
	colorChoiseWin->setBackground(Color(251, 224, 243, 140));
	ColorPicker colorPicker({0, 0, 400, 400}, colorChoiseWin);

	ContextButton<ColorPicker> colorChooseButton("Choose", {410, 140, 180, 60}, colorChoiseWin);
	colorChooseButton.setContext(&colorPicker);
	colorChooseButton.setAction(pickColor);
	colorChooseButton.setDefaultTexture(Color(251, 224, 243, 140));
	colorChooseButton.setHoverTexture(Color(251, 224, 243, 140));

	ContextButton<DynamicWindow> colorButton("Color", {200, 0, 100, 52});
	colorButton.setContext(colorChoiseWin);
	colorButton.setAction(showWin);
	colorButton.show();

	Brush brush("./skins/brush.png");
	canvas.addTool(&brush);

	Bucket bucket("./skins/bucket.png");
	canvas.addTool(&bucket);

	Eraser eraser("./skins/eraser.png");
	canvas.addTool(&eraser);

	Revealer reavealer("./skins/revealer.png");
	canvas.addTool(&reavealer);

	booba::APPCONTEXT = new booba::ApplicationContext();
	booba::APPCONTEXT->fgColor = black.mapRGBA();
	booba::APPCONTEXT->bgColor = white.mapRGBA();

	PluginManager pluginManager;
	pluginManager.loadPlugins();
	canvas.addTools(pluginManager.getTools());

	return app.run();
}
