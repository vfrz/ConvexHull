#include "main.h"

void drawEdge(sf::RenderWindow* window, Vertex* vertex)
{
	auto color = sf::Color(243, 156, 18);
	auto nextVertex = vertex->nextVertex;

	sf::Vertex line[] = {
			sf::Vertex(sf::Vector2f(vertex->point.x, vertex->point.y), color),
			sf::Vertex(sf::Vector2f(nextVertex->point.x, nextVertex->point.y), color)
	};

	window->draw(line, 2, sf::Lines);
}

void drawPolygonEdges(sf::RenderWindow* window, Polygon* polygon)
{
	if (polygon->primaryVertex == nullptr)
		return;

	drawEdge(window, polygon->primaryVertex);
	auto nextVertex = polygon->primaryVertex->nextVertex;
	while (nextVertex != polygon->primaryVertex)
	{
		drawEdge(window, nextVertex);
		nextVertex = nextVertex->nextVertex;
	}
}

void drawPoint(sf::RenderWindow* window, Vertex* vertex) {
	sf::CircleShape circle(3, 12);
	circle.setFillColor(sf::Color(46, 204, 113));
	circle.setPosition(vertex->point.x, vertex->point.y);
	window->draw(circle);
}

void drawPolygonPoints(sf::RenderWindow* window, Polygon* polygon)
{
	if (polygon->primaryVertex == nullptr)
		return;

	drawPoint(window, polygon->primaryVertex);
	auto nextVertex = polygon->primaryVertex->nextVertex;
	while (nextVertex != polygon->primaryVertex)
	{
		drawPoint(window, nextVertex);
		nextVertex = nextVertex->nextVertex;
	}
}

Polygon generatePolygon(int points)
{
	Polygon polygon;
	Vertex* nextVertex = nullptr;
	srand(time(nullptr));

	auto min = 5;
	auto maxX = WINDOW_WIDTH - min;
	auto maxY = WINDOW_HEIGHT - min;

	for (int i = 0; i < points; ++i)
	{
		auto x = min + rand() % ((maxX + 1) - min);
		auto y = min + rand() % ((maxY + 1) - min);
		nextVertex = polygon.addVertex(Point(x, y), nextVertex);
	}
	return polygon;
}

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 16;

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "ConvexHull", sf::Style::Default, settings);

	Polygon polygon = generatePolygon(100);

	window.setActive();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
		}

		window.clear(sf::Color(44, 62, 80));

		//drawPolygonEdges(&window, &polygon);
		drawPolygonPoints(&window, &polygon);

		window.display();
	}

	return 0;
}
