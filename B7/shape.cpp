#include "shape.hpp"

pochetnyi::Shape::Shape(Point &point) :
  center_(point)
{}

bool pochetnyi::Shape::isMoreLeft(const Shape &shape) const
{
  return (center_.x < shape.center_.x);
}

bool pochetnyi::Shape::isUpper(const Shape &shape) const
{
  return (center_.y > shape.center_.y);
}

namespace pochetnyi
{
  std::ostream &operator<<(std::ostream &stream, const Shape &shape)
  {
    return shape.draw(stream);
  }
}
