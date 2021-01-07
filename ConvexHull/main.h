#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Polygon.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

void drawPolygonEdges(sf::RenderWindow* window, Polygon* polygon);

void drawLine(sf::RenderWindow* window, Point from, Point to);

void drawPolygonPoints(sf::RenderWindow* window, Polygon* polygon);

void drawPoints(sf::RenderWindow* window, std::vector<Point> points);

void drawPoint(sf::RenderWindow* window, Point point);

Polygon convexHull(const std::vector<Point>& points);

std::vector<Point> generatePoints(int pointCount);

Polygon generatePolygon(int pointCount);