#include "bucket.hpp"


extern booba::ApplicationContext* booba::APPCONTEXT;
const char texture[] = "bucket.png";


BucketTool::BucketTool()
{

}

BucketTool::~BucketTool()
{

}

void BucketTool::apply(booba::Image* image, const booba::Event* event)
{
	m_fillColor = booba::APPCONTEXT->fgColor;

	switch (event->type) {
		case booba::EventType::MouseReleased:
			this->fill(image, {static_cast<int>(event->Oleg.mbedata.x), 
				               static_cast<int>(event->Oleg.mbedata.y)});
			break;

		case booba::EventType::NoEvent:
		case booba::EventType::MouseMoved:
		case booba::EventType::MousePressed:
		case booba::EventType::ButtonClicked:
		case booba::EventType::SliderMoved:
		case booba::EventType::CanvasMPressed:
		case booba::EventType::CanvasMReleased:
		case booba::EventType::CanvasMMoved:

		default:
			break;
	}
}

const char* BucketTool::getTexture() 
{
	return texture;
}

void BucketTool::buildSetupWidget()
{

}

void BucketTool::fill(booba::Image* image, const std::pair<int, int>& point)
{
	int width  = static_cast<int>(image->getW());
	int height = static_cast<int>(image->getH());

	int startPoint = point.second * width + point.first;
	uint32_t bgColor = image->getPixel(point.first, point.second);

	std::unordered_set<int> visited = {};
	std::queue<int> bfs = {};

	bfs.push(startPoint);
	visited.insert(startPoint);

	while (!bfs.empty()) {
		int current = bfs.front();
		bfs.pop();

		int curX = current % width;
		int curY = current / width;

		if (curX >= 0 && curX < width && curY >= 0 && curY < height && 
			image->getPixel(curX, curY) == bgColor)
		{
			image->setPixel(curX, curY, m_fillColor);
		}
		else {
			continue;
		}

		int adjacent[4] = {};
		adjacent[0] = curX - 1 +   curY * width;
		adjacent[1] = curX + 1 +   curY * width;
		adjacent[2] = curX + (curY - 1) * width;
		adjacent[3] = curX + (curY + 1) * width;

		for (int i = 0; i < 4; i++) {
			if (visited.find(adjacent[i]) == visited.end()) {
				bfs.push(adjacent[i]);
				visited.insert(adjacent[i]);
			}
		}
	}
}

void BucketTool::fastFill(booba::Image* image, const std::pair<int, int>& point)
{
	int width  = static_cast<int>(image->getW());
	int height = static_cast<int>(image->getH());

	int x = point.first;
	int y = point.second;
	const uint32_t bgColor = image->getPixel(x, y);

	std::queue<int> queue = {};
	
	queue.push(x);
	queue.push(x);
	queue.push(y);
	queue.push(1);

	queue.push(x);
	queue.push(x);
	queue.push(y - 1);
	queue.push(-1);

	while (!queue.empty()) {
		int x1 = queue.front();
		queue.pop();

		int x2 = queue.front();
		queue.pop();

		y = queue.front();
		queue.pop();

		int dy = queue.front();
		queue.pop();

		x = x1;

		if (image->getPixel(x, y) == bgColor) {
			while (image->getPixel(x, y) == bgColor) {
				image->setPixel(x - 1, y, m_fillColor);
				x--;
			}
		}

		if (x < x1) {
			queue.push(x);
			queue.push(x1 - 1);
			queue.push(y - dy);
			queue.push(-dy);
		}

		while (x1 <= x2) {
			while (image->getPixel(x1, y) == bgColor) {
				image->setPixel(x1, y, m_fillColor);
				x1++;

				queue.push(x);
				queue.push(x1 - 1);
				queue.push(y + dy);
				queue.push(dy);

				if (x1 - 1 > x2) {
					queue.push(x2 + 1);
					queue.push(x1 - 1);
					queue.push(y - dy);
					queue.push(-dy);
				}
			}

			x1++;

			while (x1 < x2 && image->getPixel(x1, y) != bgColor) {
				x1++;
			}

			x = x1;
		}
	}
}

void booba::init_module()
{
    BucketTool* bucketTool = new BucketTool();
    booba::addTool(bucketTool);
}

