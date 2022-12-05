#include "canvas.hpp"
#include "app.hpp"


extern booba::ApplicationContext* booba::APPCONTEXT;
extern booba::Tool* __currentImportTool__;


Canvas::Canvas(const Rect& bounds, Widget* parent):
	ContainerWidget(bounds, parent)
{
	m_drawingSurface = Surface(1920, 1080);
	m_drawingSurface.fillColor(white);

	m_copyBounds = Rect(0, 0, m_bounds.w, m_bounds.h);

	m_horizontalBar = new HScrollbar({m_bounds.x, m_bounds.y + m_bounds.h, m_bounds.w, 20});
	m_horizontalBar->show();

	m_verticalBar   = new VScrollbar({m_bounds.x + m_bounds.w, m_bounds.y, 20, m_bounds.h});
	m_verticalBar->show();

	m_cornerSquare = new Frame({m_bounds.x + m_bounds.w, m_bounds.y + m_bounds.h, 20, 20});
	m_cornerSquare->setBackground(Color(102, 102, 102, 255));
	m_cornerSquare->setFrameColor(Color(102, 102, 102, 255));
	m_cornerSquare->show();

	if (booba::APPCONTEXT) {
		m_fgColor = Color(booba::APPCONTEXT->fgColor);
		m_bgColor = Color(booba::APPCONTEXT->bgColor);
	}
}

Canvas::~Canvas()
{
	delete m_horizontalBar;
	delete m_verticalBar;
	delete m_cornerSquare;

	while (!m_prevStates.empty()) {
		Color* toDelete = m_prevStates.back();
		m_prevStates.pop_back();
		delete [] toDelete;
	}
}

void Canvas::save()
{

}

void Canvas::saveAs()
{

}

void Canvas::open()
{

}

void Canvas::addTools(std::vector<booba::Tool*>& tools)
{
	for (size_t i = 0; i < tools.size(); i++) {
		__currentImportTool__ = tools[i];
		tools[i]->buildSetupWidget();
		// m_toolManager += tools[i];
	}
}

void Canvas::setFGColor(const Color& newColor)
{
	m_fgColor = newColor;
}

void Canvas::setBGColor(const Color& newColor)
{
	m_bgColor = newColor;
}

void Canvas::addTool(Instrument* tool)
{
	m_toolsNow++;

	int curRows    = m_toolsNow / m_toolsInRow;
	int curColumns = m_toolsNow % m_toolsInRow;

	const Rect& boxBounds = m_toolBox->getBounds();
	int x = boxBounds.x + 40 + 80 * (curColumns - 1);
	int y = boxBounds.y + 40 + 80 *  curRows;

	int w = 40;
	int h = 40;

	tool->setIconPos(x, y, w, h);

	m_toolManager += tool;
}

void Canvas::addToolBox(Frame* toolBox)
{
	m_toolBox = toolBox;
	
	const Rect& boxBounds = m_toolBox->getBounds();
	m_toolsInRow = (boxBounds.w - 40) / 40;
}

void Canvas::draw()
{
	Texture* pictureTex = new Texture(m_drawingSurface);

	Renderer* renderer = getApp()->getRenderer();
	renderer->copyTexture(pictureTex, m_bounds, m_copyBounds);

	delete pictureTex;
}

bool Canvas::intersects(const Vec2& point)
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

bool Canvas::onMouseMove(const Vec2& point, const Vec2& motion)
{
	if (m_isHidden)
		return false;
	
	Vec2 relPoint = point - Vec2(m_bounds.x, m_bounds.y) + Vec2(m_copyBounds.x, m_copyBounds.y);

	bool res = false;
	if (this->intersects(point)) res &= m_toolManager.reactToMouseMove (m_drawingSurface, relPoint, motion);
	else                         res &= m_toolManager.reactToMouseLeave(m_drawingSurface, relPoint, motion);

	res &= m_childrenManager.callOnMouseMove(point, motion);

	return res;
}

bool Canvas::onButtonClick(MouseButton button, const Vec2& point)
{
	bool res = m_toolManager.changeTool(button, point);

	if (m_isHidden || !this->intersects(point))
		return res;

	size_t pixelsNumber = static_cast<size_t>(m_drawingSurface.getWidth() * m_drawingSurface.getHeight());
	size_t sizeofPixel  = sizeof (Color);

	Color* newState = new Color[pixelsNumber];
	std::memcpy(newState, m_drawingSurface.getPixmap(), pixelsNumber * sizeofPixel);
	m_prevStates.push_back(newState);

	if (m_prevStates.size() > m_maxStates)
		m_prevStates.pop_front();

	Vec2 relPoint = point - Vec2(m_bounds.x, m_bounds.y) + Vec2(m_copyBounds.x, m_copyBounds.y);
	res &= m_toolManager.reactToButtonClick(m_drawingSurface, button, relPoint);
	res &= m_childrenManager.callOnButtonClick(button, point);

	return res;
}

bool Canvas::onButtonRelease(MouseButton button, const Vec2& point)
{
	if (m_isHidden || !this->intersects(point))
		return false;

	Vec2 relPoint = point - Vec2(m_bounds.x, m_bounds.y) + Vec2(m_copyBounds.x, m_copyBounds.y);
	bool res = m_toolManager.reactToButtonRelease(m_drawingSurface, button, relPoint);
	res &= m_childrenManager.callOnButtonRelease(button, point);

	return res;
}

bool Canvas::onKeyPress(Key key)
{
	if (m_isHidden)
		return false;

	bool res = m_toolManager.reactToKeyPress(m_drawingSurface, key);
	res &= m_childrenManager.callOnKeyPress(key);

	if (key == SDLK_LCTRL) {
		m_ctrlPressed = true;
	}

	if (key == SDLK_z && m_ctrlPressed) {
		if (!m_prevStates.size()) {
			return res;
		}

		Color* prevPixmap = m_prevStates.back();
		m_prevStates.pop_back();

		size_t pixelsNumber = static_cast<size_t>(m_drawingSurface.getWidth() * m_drawingSurface.getHeight());
		size_t sizeofPixel  = sizeof (Color);

		std::memcpy(m_drawingSurface.getPixmap(), prevPixmap, pixelsNumber * sizeofPixel);
		delete [] prevPixmap;

		res &= true;
	}

	return res;
}

bool Canvas::onKeyRelease(Key key)
{
	if (m_isHidden)
		return false;

	bool res = m_toolManager.reactToKeyRelease(m_drawingSurface, key);
	res &= m_childrenManager.callOnKeyRelease(key);

	if (key == SDLK_LCTRL) {
		m_ctrlPressed = false;
	}

	return res;
}

bool Canvas::onTick(Time time)
{
	float maxX = static_cast<float>(m_drawingSurface.getWidth() - m_bounds.w);
	int   newX = static_cast<int>(maxX * m_horizontalBar->getValue());
	m_copyBounds.x = newX;

	float maxY = static_cast<float>(m_drawingSurface.getHeight() - m_bounds.h);
	int   newY = static_cast<int>(maxY * m_verticalBar->getValue());
	m_copyBounds.y = newY;

	bool res = m_toolManager.reactToTick(m_drawingSurface, time);
	res &= m_childrenManager.callOnTick(time);

	if (m_isHidden)
		return res;

	this->draw();
	return true;
}
