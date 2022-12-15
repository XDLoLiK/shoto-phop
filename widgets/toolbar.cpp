#include "toolbar.hpp"
#include "app.hpp"

void selectTool(ToolSelectContext* context)
{
	booba::Tool* tool = context->tool;
	ContextButton<ToolSelectContext>* btn = context->btn;
	Toolbar* toolbar = context->toolbar;

	booba::Tool* curTool = ToolManager::getToolManager()->getCurTool();
	const std::vector<Widget*>* wids = PluginManager::getPluginManager()->getToolWidgets(curTool);

	if (wids != nullptr) {
		for (size_t i = 0; i < wids->size(); i++) {
			wids->at(i)->setHidden(true);
		}
	}

	ToolManager::getToolManager()->chooseTool(tool);
	wids = PluginManager::getPluginManager()->getToolWidgets(tool);

	if (wids != nullptr) {
		for (size_t i = 0; i < wids->size(); i++) {
			wids->at(i)->setHidden(false);
		}
	}

	for (size_t i = 0; i < toolbar->getSelectors().size(); i++) {
		toolbar->getSelectors().at(i)->setFrameColor(white);
	}
	btn->setFrameColor(black);
}

Toolbar::Toolbar(const Rect& bounds, Widget* parent):
	ContainerWidget(bounds, parent)
{
	this->setBackground(white);
	this->setFrameColor(NO_FRAME);
}

Toolbar::~Toolbar()
{
	for (size_t i = 0; i < m_selectors.size(); i++) {
		delete m_selectors[i];
	}

	for (size_t i = 0; i < m_contexts.size(); i++) {
		delete m_contexts[i];
	}
}

const std::vector<ContextButton<ToolSelectContext>*>& Toolbar::getSelectors()
{
	return m_selectors;
}

void Toolbar::addTool(booba::Tool* tool)
{
	int w = ICON_DEFAULT_SIZE;
	int h = ICON_DEFAULT_SIZE;
	int x = (m_bounds.w - w) / 2;
	int y = h * (m_selectors.size() * 2 + 1);
	Rect newBounds = {x, y, w, h};

	ContextButton<ToolSelectContext>* newButton = new ContextButton<ToolSelectContext>("", newBounds, black, this);

	newButton->setFrameColor(NO_FRAME);
	newButton->setBackground(std::string("./plugins/") + std::string(tool->getTexture()));

	ToolSelectContext* newContext = new ToolSelectContext(tool, newButton, this);
	m_contexts.push_back(newContext);

	newButton->setContext(newContext);
	newButton->setAction(selectTool);
	newButton->setHidden(false);

	m_selectors.push_back(newButton);
}

void Toolbar::addTools(const std::vector<booba::Tool*>& tools)
{
	for (size_t i = 0; i < tools.size(); i++) {
		this->addTool(tools[i]);
	}
}

void Toolbar::draw()
{
	if (m_isHidden) {
		return;
	}

	this->drawSkin (this->getRealBounds());
	this->drawFrame(this->getRealBounds());
}

bool Toolbar::intersects(const Vec2& point)
{
	if (point.getX() < m_bounds.x || 
		point.getX() > m_bounds.x + m_bounds.w)
	{
		return false;
	}

	if (point.getY() < m_bounds.y || 
		point.getY() > m_bounds.y + m_bounds.h)
	{
		return false;
	}

	return true;
}

void Toolbar::shiftIcons(int val)
{
	for (size_t i = 0; i < m_selectors.size(); i++) {
		m_selectors[i]->setGeometry(m_selectors[i]->getBounds().x + val, m_selectors[i]->getBounds().y);
	}
}

bool Toolbar::onMouseMove(const Vec2& point, const Vec2& motion)
{
	static int maxW = m_bounds.w + 20;
	static int minW = m_bounds.w;

	if (m_isHidden) {
		return false;
	}

	bool res = m_childrenManager.callOnMouseMove(point, motion);

	if (this->intersects(point)) {
		if (m_bounds.w < maxW) {
			m_bounds.w += 2;
			this->shiftIcons(1);
			res |= 1;
		}
	}
	else {
		if (m_bounds.w > minW) {
			m_bounds.w -= 2;
			this->shiftIcons(-1);
			res |= 1;
		}
	}

	return res;
}

bool Toolbar::onButtonClick(MouseButton button, const Vec2& point)
{
	if (m_isHidden) {
		return false;
	}

	return m_childrenManager.callOnButtonClick(button, point);
}

bool Toolbar::onButtonRelease(MouseButton button, const Vec2& point)
{
	if (m_isHidden) {
		return false;
	}

	return m_childrenManager.callOnButtonRelease(button, point);
}

bool Toolbar::onKeyPress(Key key)
{
	if (m_isHidden) {
		return false;
	}

	return m_childrenManager.callOnKeyPress(key);
}

bool Toolbar::onKeyRelease(Key key)
{
	if (m_isHidden) {
		return false;
	}

	return m_childrenManager.callOnKeyRelease(key);
}

bool Toolbar::onTick(Time time)
{
	if (m_isHidden) {
		return false;
	}

	this->draw();
	return m_childrenManager.callOnTick(time);
}
