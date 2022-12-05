// #include "toolbar.hpp"
// #include "app.hpp"

// void selectTool(Tool* tool)
// {
// 	getPluginManager()->selectTool(tool);
// }

// Toolbar::Toolbar(const Rect& bounds = {0, 0, 0, 0}, Widget* parent = nullptr):
// 	ContainerWidget(bounds, parent)
// {

// }

// Toolbar::~Toolbar()
// {
// 	for (size_t i = 0; i < m_selectors.size(); i++) {
// 		delete m_selectors[i];
// 	}
// }

// void linkCanvas(Canvas* canvas)
// {

// }

// void Toolbar::addTool(Tool* tool)
// {


// 	ContextButton<Tool> newButton = new ContextButton<Tool>();
// 	newButton.setContext(tool);
// 	newButton.setAction(selectTool);

// 	m_selectors.push_back(newButton);
// }
