#pragma once

#include <vector>
#include "Vertex.h"

class Polygon
{
public:
    Vertex* primaryVertex;

    Vertex *addVertex(const Point &vertexPosition, Vertex *previousVertex);
	void removeVertex(Vertex *vertex);

	std::vector<Vertex*> getVertices() const;
};

