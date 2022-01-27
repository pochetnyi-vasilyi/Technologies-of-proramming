#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

namespace pochetnyi
{
  class Circle : public Shape
  {
  public:
    Circle(Point point);

    std::ostream &draw(std::ostream &stream) const override;
  };
}

#endif
