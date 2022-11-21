#include "bucket.hpp"

Bucket::Bucket(const std::string& icon, int x, int y):
	Instrument(icon, x, y)
{

}

Bucket::~Bucket()
{

}

bool Bucket::apply(Surface* surface, booba::Event* event)
{
	bool res = false;

	switch (event->type) {
		case booba::EventType::MouseReleased:
			this->fill(surface, {event->Oleg.mbedata.x, event->Oleg.mbedata.y});

			res = true;
			break;

		case booba::EventType::NoEvent:
		case booba::EventType::MouseMoved:
		case booba::EventType::MousePressed:
		case booba::EventType::ButtonClicked:
		case booba::EventType::ScrollbarMoved:
		case booba::EventType::CanvasMPressed:
		case booba::EventType::CanvasMReleased:
		case booba::EventType::CanvasMMoved:

		default:
			break;
	}

	return res;
}

void Bucket::fill(Surface* surface, std::pair<int, int> point)
{
	int width  = 0;
	int height = 0;
	Color* pixmap = surface->getPixmap(&width, &height);

	int startPoint = point.second * width + point.first;
	Color bgColor  = pixmap[startPoint];

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
			pixmap[width * curY + curX] == bgColor)
		{
			pixmap[width * curY + curX] = m_fillColor;
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

void Bucket::fastFill(Surface* surface, std::pair<int, int> point)
{
	int width  = 0;
	int height = 0;
	Color* pixmap = surface->getPixmap(&width, &height);

	int x = point.first;
	int y = point.second;
	const Color bgColor  = pixmap[y * width + x];

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

		if (pixmap[width * y + x] == bgColor) {
			while (pixmap[width * y + x - 1] == bgColor) {
				pixmap[width * y + (x - 1)] = m_fillColor;
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
			while (pixmap[width * y + x1] == bgColor) {
				pixmap[width * y + x1] = m_fillColor;
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

			while (x1 < x2 && pixmap[width * y + x1] != bgColor) {
				x1++;
			}

			x = x1;
		}
	}
}
