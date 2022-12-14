#include "canvas.hpp"
#include "app.hpp"

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
	res &= ToolManager::getToolManager()->reactToMouseMove (m_drawingSurface, relPoint, motion);
	res &= m_childrenManager.callOnMouseMove(point, motion);

	return res;
}

bool Canvas::onButtonClick(MouseButton button, const Vec2& point)
{
	if (m_isHidden || !this->intersects(point))
		return false;

	bool res = m_childrenManager.callOnButtonClick(button, point);
	if (res) {
		return res;
	}

	size_t pixelsNumber = static_cast<size_t>(m_drawingSurface.getWidth() * m_drawingSurface.getHeight());
	size_t sizeofPixel  = sizeof (Color);

	Color* newState = new Color[pixelsNumber];
	std::memcpy(newState, m_drawingSurface.getPixmap(), pixelsNumber * sizeofPixel);
	m_prevStates.push_back(newState);

	if (m_prevStates.size() > m_maxStates)
		m_prevStates.pop_front();

	Vec2 relPoint = point - Vec2(m_bounds.x, m_bounds.y) + Vec2(m_copyBounds.x, m_copyBounds.y);
	res &= ToolManager::getToolManager()->reactToButtonClick(m_drawingSurface, button, relPoint);

	return res;
}

bool Canvas::onButtonRelease(MouseButton button, const Vec2& point)
{
	if (m_isHidden || !this->intersects(point))
		return false;

	Vec2 relPoint = point - Vec2(m_bounds.x, m_bounds.y) + Vec2(m_copyBounds.x, m_copyBounds.y);
	bool res = ToolManager::getToolManager()->reactToButtonRelease(m_drawingSurface, button, relPoint);
	res &= m_childrenManager.callOnButtonRelease(button, point);

	return res;
}

bool Canvas::onKeyPress(Key key)
{
	if (m_isHidden)
		return false;

	bool res = ToolManager::getToolManager()->reactToKeyPress(m_drawingSurface, key);
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

	bool res = ToolManager::getToolManager()->reactToKeyRelease(m_drawingSurface, key);
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

	bool res = ToolManager::getToolManager()->reactToTick(m_drawingSurface, time);
	res &= m_childrenManager.callOnTick(time);

	if (m_isHidden)
		return res;

	this->draw();
	return true;
}
