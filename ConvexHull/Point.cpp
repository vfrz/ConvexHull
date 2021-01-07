#include "Point.h"

Point::Point() : x(-1), y(-1)
{
}

Point::Point(int x, int y) : x(x), y(y)
{
}

bool Point::onLeft(const Point& a, const Point& b) const
{
	return (b.x - a.x) * (y - a.y) - (x - a.x) * (b.y - a.y) > 0;
}