#include "app.hpp"
#include "button.hpp"
#include "frame.hpp"
#include "canvas.hpp"
#include "brush.hpp"
#include "bucket.hpp"
#include "eraser.hpp"
#include "revealer.hpp"
#include "drop_list.hpp"
#include "context_button.hpp"
#include "dynamic_window.hpp"
#include "plugin_manager.hpp"
#include "color_chooser.hpp"

booba::ApplicationContext* booba::APPCONTEXT = nullptr;

void showWin(DynamicWindow* win)
{
	win->show();
}

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

	Button closeButton("Exit", {0, 0, 100, 52});
	closeButton.buttonClick += METHOD(app, App::close);
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

	DynamicWindow* colorChoiseWin = new DynamicWindow({100, 100, 600, 600});
	
	ColorPicker test({100, 100, 400, 400});
	test.show();

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

	return app.run();
}
