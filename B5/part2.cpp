#include "parts.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>
#include "shape.hpp"

void pochetnyi::part2()
{
  std::vector<Shape> shapes{ std::istream_iterator<Shape>(std::cin), std::istream_iterator<Shape>() };
  if ( !std::cin.eof() && std::cin.fail() )
  {
    throw std::runtime_error("Invalid input!");
  }

  size_t triangles = 0;
  size_t rectangles = 0;
  size_t squares = 0;
  size_t vertices = 0;

  std::for_each(shapes.begin(), shapes.end(), [&](const Shape &shape)
  {
    vertices += shape.points.size();
    switch (shape.type)
    {
      case ShapeType::TRIANGLE:
        triangles++;
        break;
      case ShapeType::SQUARE:
        squares++;
        rectangles++;
        break;
      case ShapeType::RECTANGLE:
        rectangles++;
        break;
      case ShapeType::OTHER:
        break;
    }
  });

  shapes.erase(std::remove_if(shapes.begin(), shapes.end(), [](const Shape &shape)
      { return shape.points.size() == 5; }), shapes.end());

  std::cout << "Vertices: " << vertices << "\nTriangles: " << triangles << "\nSquares: " << squares
      << "\nRectangles: " << rectangles << "\n";

  std::vector<Point> points;
  for (Shape &shape : shapes)
  {
    points.push_back(shape.points[0]);
  }

  std::cout << "Points:";
  std::copy(points.begin(), points.end(), std::ostream_iterator<Point>(std::cout, " "));

  std::sort(shapes.begin(), shapes.end());
  std::cout << "\nShapes:\n";
  std::copy(shapes.begin(), shapes.end(), std::ostream_iterator<Shape>(std::cout, "\n"));
}
