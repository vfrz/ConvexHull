#pragma once

class Point
{
public:
	Point(int x, int y);
	Point();
    int x;
    int y;
	bool onLeft(const Point &a, const Point &b) const;
};
