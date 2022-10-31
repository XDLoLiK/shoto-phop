#ifndef RECT_HPP
#define RECT_HPP

class Rect
{
public:
	Rect(int xc = 0, int yc = 0, int width = 0, int height = 0):
		x(xc),
		y(yc),
		w(width),
		h(height)
	{

	}

public:
	int x = 0;
	int y = 0;
	int w = 0;
	int h = 0;
};

#endif // RECT_HPP
