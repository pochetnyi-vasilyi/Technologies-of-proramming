#include "square.hpp"

pochetnyi::Square::Square(Point point) :
  Shape(point)
{}

std::ostream &pochetnyi::Square::draw(std::ostream &stream) const
{
  stream << "SQUARE " << center_ << "\n";
  return stream;
}
