#include "main.h"

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 16;

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "ConvexHull", sf::Style::Default, settings);

	Polygon polygon = generatePolygon(100);

	window.setActive();

	while (window.isOpen())
	{
		sf::Event event{};
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
		}

		window.clear(sf::Color(44, 62, 80));

		drawPolygonEdges(&window, &polygon);
		drawPolygonPoints(&window, &polygon);

		window.display();
	}

	return 0;
}

void drawPolygonEdges(sf::RenderWindow* window, Polygon* polygon)
{
	if (polygon->primaryVertex == nullptr)
		return;

	drawLine(window, polygon->primaryVertex->point, polygon->primaryVertex->nextVertex->point);
	auto currentVertex = polygon->primaryVertex->nextVertex;
	while (currentVertex != polygon->primaryVertex)
	{
		drawLine(window, currentVertex->point, currentVertex->nextVertex->point);
		currentVertex = currentVertex->nextVertex;
	}
}

void drawLine(sf::RenderWindow* window, Point from, Point to)
{
	auto color = sf::Color(243, 156, 18);

	sf::Vertex line[] = {
			sf::Vertex(sf::Vector2f(from.x, from.y), color),
			sf::Vertex(sf::Vector2f(to.x, to.y), color)
	};

	window->draw(line, 2, sf::Lines);
}

void drawPolygonPoints(sf::RenderWindow* window, Polygon* polygon)
{
	if (polygon->primaryVertex == nullptr)
		return;

	drawPoint(window, polygon->primaryVertex->point);
	auto nextVertex = polygon->primaryVertex->nextVertex;
	while (nextVertex != polygon->primaryVertex)
	{
		drawPoint(window, nextVertex->point);
		nextVertex = nextVertex->nextVertex;
	}
}

void drawPoint(sf::RenderWindow* window, Point point)
{
	sf::CircleShape circle(3, 12);
	circle.setFillColor(sf::Color(46, 204, 113));
	circle.setPosition(point.x, point.y);
	circle.setOrigin(circle.getRadius(), circle.getRadius());
	window->draw(circle);
}

Polygon generatePolygon(int points)
{
	Polygon polygon{};
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