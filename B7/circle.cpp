#include "circle.hpp"

pochetnyi::Circle::Circle(Point point) :
  Shape(point)
{}

std::ostream &pochetnyi::Circle::draw(std::ostream &stream) const
{
  stream << "CIRCLE " << center_ << "\n";
  return stream;
}
