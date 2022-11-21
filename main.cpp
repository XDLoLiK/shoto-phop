#include "app.hpp"
#include "button.hpp"
#include "frame.hpp"
#include "canvas.hpp"
#include "brush.hpp"
#include "bucket.hpp"
#include "eraser.hpp"
#include "drop_list.hpp"

/**
 *
 * Tool: reactToMouseLeave
 *
 */

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

	Button toolsButton("Color", {200, 0, 100, 52});
	toolsButton.show();

	Brush* brush = new Brush("./skins/brush.png");
	canvas.addTool(brush);

	Bucket* bucket = new Bucket("./skins/bucket.png");
	canvas.addTool(bucket);

	Eraser* eraser = new Eraser("./skins/eraser.png");
	canvas.addTool(eraser);

	return app.run();
}
