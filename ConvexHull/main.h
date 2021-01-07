#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Polygon.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

void drawPolygonEdges(sf::RenderWindow *window, Polygon *polygon);
void drawLine(sf::RenderWindow *window, Point from, Point to);

void drawPolygonPoints(sf::RenderWindow *window, Polygon *polygon);
void drawPoint(sf::RenderWindow *window, Point point);

Polygon generatePolygon(int points);