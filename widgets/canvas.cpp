#include <dialogs.hpp>
#include <lodepng.hpp>
#include <cstdio>

#include "canvas.hpp"
#include "app.hpp"

Canvas::Canvas(const Rect& bounds, Widget* parent):
	ContainerWidget(bounds, parent)
{
	m_drawingSurface = new Surface(1920, 1080);
	m_drawingSurface->fillColor(white);
	m_historyBuffer.initBuffer(m_drawingSurface);

	Surface* newSurf = new Surface(1920, 1080);
	newSurf->fillColor(white);
	m_layers.push_back(m_drawingSurface);
	m_layers.push_back(newSurf);

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
}

void Canvas::save()
{
	if (m_curFile.length() == 0) {
		this->saveAs();
		return;
	}

	int width  = m_drawingSurface->getWidth();
	int height = m_drawingSurface->getHeight();
	uint8_t* data = reinterpret_cast<uint8_t*>(m_drawingSurface->getPixmap());

	uint8_t* img = new uint8_t[width * height * 4];
    for(int i = 0; i < width * height * 4; i++) {
        img[i] = data[i];
    }

    lodepng::encode(m_curFile, img, width, height, LCT_RGBA);
    delete[] img;
}

void Canvas::saveAs()
{
	auto file = pfd::save_file("Choose file to save",
                               getCurrentWorkingDir() + pfd::path::separator() + m_curFile,
                               { "All Files", "*" },
                               pfd::opt::force_overwrite);

	int width  = m_drawingSurface->getWidth();
	int height = m_drawingSurface->getHeight();
	uint8_t* data = reinterpret_cast<uint8_t*>(m_drawingSurface->getPixmap());

	uint8_t* img = new uint8_t[width * height * 4];
    for(int i = 0; i < width * height * 4; i++) {
        img[i] = data[i];
    }

    if (file.result().size()) {
    	lodepng::encode(file.result(), img, width, height, LCT_RGBA);
    	m_curFile = file.result();
    }

    delete[] img;
}

void Canvas::open()
{
	auto file = pfd::open_file("Choose files to read", getCurrentWorkingDir(),
                               { "All Files", "*" },
                               pfd::opt::multiselect);

	std::vector<uint8_t> img = {};
	uint32_t width  = static_cast<uint32_t>(m_drawingSurface->getWidth());
	uint32_t height = static_cast<uint32_t>(m_drawingSurface->getHeight());

	if (!file.result().size()) {
		return;
	}

	uint32_t error = lodepng::decode(img, width, height, file.result().at(0), LCT_RGBA);
	if (error) {
		std::cout << lodepng_error_text(error) << std::endl;
	}

	uint8_t* data = reinterpret_cast<uint8_t*>(m_drawingSurface->getPixmap());
	for (int i = 0; i < width * height * 4; i++) {
		data[i] = img[i];
	}

	m_curFile = file.result().at(0);
}

void Canvas::draw()
{
	Texture* pictureTex = new Texture(*m_drawingSurface);

	Renderer* renderer = getApp()->getRenderer();
	renderer->copyTexture(pictureTex, this->getRealBounds(), m_copyBounds);

	delete pictureTex;
}

bool Canvas::intersects(const Vec2& point)
{
	const Rect& bounds = this->getRealBounds();

	if (point.getX() < bounds.x || 
		point.getX() > bounds.x + bounds.w)
	{
		return false;
	}

	if (point.getY() < bounds.y || 
		point.getY() > bounds.y + bounds.h)
	{
		return false;
	}

	return true;
}

bool Canvas::onMouseMove(const Vec2& point, const Vec2& motion)
{
	if (m_isHidden)
		return false;
	
	bool res = false;

	if (!this->intersects(point)) {
		res &= ToolManager::getToolManager()->reactToMouseLeave(*m_drawingSurface);
		res &= m_childrenManager.callOnMouseMove(point, motion);
		return res;
	}

	const Rect& bounds = this->getRealBounds();
	Vec2 relPoint = point - Vec2(bounds.x, bounds.y) + Vec2(m_copyBounds.x, m_copyBounds.y);

	res &= ToolManager::getToolManager()->reactToMouseMove(*m_drawingSurface, relPoint, motion);
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

	const Rect& bounds = this->getRealBounds();
	Vec2 relPoint = point - Vec2(bounds.x, bounds.y) + Vec2(m_copyBounds.x, m_copyBounds.y);
	res &= ToolManager::getToolManager()->reactToButtonClick(*m_drawingSurface, button, relPoint);

	return res;
}

bool Canvas::onButtonRelease(MouseButton button, const Vec2& point)
{
	if (m_isHidden || !this->intersects(point))
		return false;

	m_historyBuffer.addState(m_drawingSurface);

	const Rect& bounds = this->getRealBounds();
	Vec2 relPoint = point - Vec2(bounds.x, bounds.y) + Vec2(m_copyBounds.x, m_copyBounds.y);
	bool res = ToolManager::getToolManager()->reactToButtonRelease(*m_drawingSurface, button, relPoint);
	res &= m_childrenManager.callOnButtonRelease(button, point);

	return res;
}

bool Canvas::onKeyPress(Key key)
{
	if (m_isHidden)
		return false;

	bool res = ToolManager::getToolManager()->reactToKeyPress(*m_drawingSurface, key);
	res &= m_childrenManager.callOnKeyPress(key);

	if (key == SDLK_LCTRL) {
		m_ctrlPressed = true;
	}

	if (m_ctrlPressed) {
		switch (key) {
			case SDLK_s:
				this->save();
				break;

			case SDLK_a:
				this->saveAs();
				break;

			case SDLK_o:
				this->open();
				break;

			case SDLK_z:
				m_historyBuffer.prevState(m_drawingSurface);
				res &= true;
				break;

			case SDLK_y:
				m_historyBuffer.nextState(m_drawingSurface);
				res &= true;
				break;

			case SDLK_RIGHT:
				m_drawingSurface = m_layers[1];
				break;

			case SDLK_LEFT:
				m_drawingSurface = m_layers[0];
				break;

			default:
				break;
		}
	}

	return res;
}

bool Canvas::onKeyRelease(Key key)
{
	if (m_isHidden)
		return false;

	bool res = ToolManager::getToolManager()->reactToKeyRelease(*m_drawingSurface, key);
	res &= m_childrenManager.callOnKeyRelease(key);

	if (key == SDLK_LCTRL) {
		m_ctrlPressed = false;
	}

	return res;
}

bool Canvas::onTick(Time time)
{
	if (m_isHidden)
		return false;

	bool res = false;

	float maxX = static_cast<float>(m_drawingSurface->getWidth() - m_bounds.w);
	int   newX = static_cast<int>(maxX * m_horizontalBar->getValue());
	m_copyBounds.x = newX;

	float maxY = static_cast<float>(m_drawingSurface->getHeight() - m_bounds.h);
	int   newY = static_cast<int>(maxY * m_verticalBar->getValue());
	m_copyBounds.y = newY;

	res = ToolManager::getToolManager()->reactToTick(*m_drawingSurface, static_cast<uint64_t>(time));
	res &= m_childrenManager.callOnTick(time);

	this->draw();
	return true;
}
