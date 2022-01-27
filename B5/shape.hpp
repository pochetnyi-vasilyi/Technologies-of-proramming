#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <iostream>
#include <vector>
#include "../common/point.hpp"

namespace pochetnyi
{
  enum class ShapeType
  {
    TRIANGLE,
    SQUARE,
    RECTANGLE,
    OTHER
  };

  struct Shape
  {
    std::vector<Point> points;
    ShapeType type;
  };

  bool isTriangle(const Shape &shape);
  bool isRectangle(const Shape &shape);
  bool isSquare(const Shape &shape);
  ShapeType getType(const Shape &shape);
  bool operator<(const Shape &lhs, const Shape &rhs);

  std::istream &operator>>(std::istream &in, Shape &shape);
  std::ostream &operator<<(std::ostream &out, const Shape &shape);
}

#endif
