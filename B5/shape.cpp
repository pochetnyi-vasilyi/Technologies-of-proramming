#include "shape.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>

bool pochetnyi::isTriangle(const Shape &shape)
{
  return (shape.points.size() == 3);
}

bool pochetnyi::isRectangle(const Shape &shape)
{
  if (shape.points.size() == 4)
  {
    return (getLength(shape.points[0], shape.points[2]) == getLength(shape.points[1], shape.points[3]));
  }
  return false;
}

bool pochetnyi::isSquare(const Shape &shape)
{
  if (isRectangle(shape))
  {
    return (getLength(shape.points[0], shape.points[1]) == getLength(shape.points[1], shape.points[2]));
  }
  return false;
}

pochetnyi::ShapeType pochetnyi::getType(const Shape &shape)
{
  if (isTriangle(shape))
  {
    return ShapeType::TRIANGLE;
  }
  else if (isSquare(shape))
  {
    return ShapeType::SQUARE;
  }
  else if (isRectangle(shape))
  {
    return ShapeType::RECTANGLE;
  }
  else
  {
    return ShapeType::OTHER;
  }
}

bool pochetnyi::operator<(const Shape &lhs, const Shape &rhs)
{
  return lhs.type < rhs.type;
}

std::ostream &pochetnyi::operator<<(std::ostream &out, const Shape &shape)
{
  out << shape.points.size() << ' ';
  std::copy(shape.points.cbegin(), shape.points.cend(), std::ostream_iterator<Point>(out, " "));
  return out;
}

std::istream &pochetnyi::operator>>(std::istream &in, Shape &shape)
{
  size_t vertices;
  in >> vertices;
  std::string str;
  std::getline(in, str);
  std::istringstream iss(str);
  Shape tempShape = { { std::istream_iterator<Point>(iss), std::istream_iterator<Point>() }, ShapeType::OTHER };

  if ((tempShape.points.size() < 3) || (tempShape.points.size() != vertices))
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  tempShape.type = getType(tempShape);
  std::swap(shape, tempShape);

  return in;
}
