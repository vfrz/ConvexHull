cmake_minimum_required(VERSION 3.17)
project(ConvexHull)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5.1 COMPONENTS graphics system window REQUIRED)

add_executable(ConvexHull main.cpp Point.cpp Point.h Vertex.cpp Vertex.h Polygon.cpp Polygon.h main.h)

target_link_libraries(ConvexHull sfml-graphics)