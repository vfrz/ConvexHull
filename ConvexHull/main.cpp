#include "main.h"

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 16;

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "ConvexHull", sf::Style::Default, settings);

	//Polygon polygon = generatePolygon(100);

	auto points = generatePoints(10);
	auto polygon = convexHull(points);

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

		//drawPolygonEdges(&window, &polygon);
		//drawPolygonPoints(&window, &polygon);
		drawPoints(&window, points);
		drawPolygonEdges(&window, &polygon);

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

void drawPoints(sf::RenderWindow* window, std::vector<Point> points)
{
	for (auto& p : points)
	{
		drawPoint(window, p);
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

Polygon convexHull(const std::vector<Point>& points)
{
	if (points.size() < 3)
		throw std::runtime_error("Cannot convex hull for less than 3 points");

	auto sorted = std::vector(points);

	std::sort(sorted.begin(), sorted.end(), [](Point a, Point b)
	{
		return a.x < b.x || (a.x == b.x && a.y < b.y);
	});

	std::vector<Point> hull(2 * sorted.size());
	auto k = 0;

	for (int i = 0; i < sorted.size(); ++i)
	{
		while (k >= 2 && !sorted[i].onLeft(hull[k - 2], hull[k - 1]))
			k--;
		hull[k++] = sorted[i];
	}

	for (unsigned long i = sorted.size() - 1, t = k + 1; i > 0; --i)
	{
		while (k >= t && !sorted[i - 1].onLeft(hull[k - 2], hull[k - 1]))
			k--;
		hull[k++] = sorted[i - 1];
	}

	hull.resize(k - 1);

	Polygon polygon;

	Vertex* currentVertex = nullptr;

	for (auto& p : hull)
	{
		currentVertex = polygon.addVertex(p, currentVertex);
	}

	return polygon;
}

std::vector<Point> generatePoints(int pointCount)
{
	std::vector<Point> points;

	auto min = 5;
	auto maxX = WINDOW_WIDTH - min;
	auto maxY = WINDOW_HEIGHT - min;

	srand(time(NULL));

	for (int i = 0; i < pointCount; ++i)
	{
		auto x = min + rand() % ((maxX + 1) - min);
		auto y = min + rand() % ((maxY + 1) - min);
		points.emplace_back(Point(x, y));
	}

	return points;
}

Polygon generatePolygon(int pointCount)
{
	Polygon polygon{};
	Vertex* nextVertex = nullptr;

	auto points = generatePoints(pointCount);

	for (auto& point : points)
		nextVertex = polygon.addVertex(point, nextVertex);

	return polygon;
}