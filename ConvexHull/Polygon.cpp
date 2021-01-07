#include "Polygon.h"

Vertex* Polygon::addVertex(const Point& vertexPosition, Vertex* previousVertex)
{
	auto nouveauSommet = new Vertex(vertexPosition);

	if (previousVertex == nullptr)
	{
		nouveauSommet->nextVertex = nouveauSommet;
		nouveauSommet->previousVertex = nouveauSommet;
		this->primaryVertex = nouveauSommet;
	}
	else
	{
		nouveauSommet->previousVertex = previousVertex;
		nouveauSommet->nextVertex = previousVertex->nextVertex;
		previousVertex->nextVertex->previousVertex = nouveauSommet;
		previousVertex->nextVertex = nouveauSommet;
	}

	return nouveauSommet;
}

void Polygon::removeVertex(Vertex* vertex)
{
	vertex->previousVertex->nextVertex = vertex->nextVertex;
	vertex->nextVertex->previousVertex = vertex->previousVertex;
	delete vertex;
}

std::vector<Vertex*> Polygon::getVertices() const
{
	std::vector<Vertex*> vertices;

	auto currentVertex = primaryVertex;
	do {
		vertices.emplace_back(currentVertex);
		currentVertex = currentVertex->nextVertex;
	} while(currentVertex != primaryVertex);

	return vertices;
}
