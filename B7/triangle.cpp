#include "triangle.hpp"

pochetnyi::Triangle::Triangle(Point point) :
  Shape(point)
{}

std::ostream &pochetnyi::Triangle::draw(std::ostream &stream) const
{
  stream << "TRIANGLE " << center_ << "\n";
  return stream;
}
