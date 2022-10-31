#include "app.hpp"
#include "user_widgets.hpp"

int main()
{
	App app("test");

	Frame* rayTracer = new Frame();
	rayTracer->setGeometry({0, 125, 600, 600});
	rayTracer->setTexture("skins/ray_tracer_high.png");
	rayTracer->show();

	Frame* menuFrame = new Frame();
	menuFrame->setGeometry({0, 0, 800, 100});
	menuFrame->setTexture("./skins/menu_frame.png");
	menuFrame->show();

	CloseButton* closeButton = new CloseButton("close", menuFrame);
	closeButton->setGeometry({50, 25, 100, 50});
	closeButton->setTexture("skins/close_button.png");
	closeButton->show();

	DropList* chooseGraphicsList = new DropList("choose", menuFrame);
	chooseGraphicsList->setGeometry({175, 25, 100, 50});
	chooseGraphicsList->setTexture("skins/graphics_button.png");

	ChooseButton* lowGraphics = new ChooseButton("", chooseGraphicsList, 
		                                   rayTracer, "skins/ray_tracer_low.png");
	lowGraphics->setGeometry({0, 50, 100, 50});
	lowGraphics->setTexture("skins/low.png");

	ChooseButton* midGraphics = new ChooseButton("", chooseGraphicsList,
		                                   rayTracer, "skins/ray_tracer_mid.png");
	midGraphics->setGeometry({0, 100, 100, 50});
	midGraphics->setTexture("skins/mid.png");

	ChooseButton* highGraphics = new ChooseButton("", chooseGraphicsList,
		                                    rayTracer, "skins/ray_tracer_high.png");
	highGraphics->setGeometry({0, 150, 100, 50});
	highGraphics->setTexture("skins/high.png");

	return app.run();
}
