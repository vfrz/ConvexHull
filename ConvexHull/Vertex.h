#pragma once

#include "Point.h"

class Vertex
{
public:
    Vertex(const Point &point);

    Point point;
    Vertex *nextVertex;
    Vertex *previousVertex;
};

