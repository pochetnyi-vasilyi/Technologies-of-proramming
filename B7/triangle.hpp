#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "shape.hpp"

namespace pochetnyi
{
  class Triangle : public Shape
  {
  public:
    Triangle(Point point);

    std::ostream &draw(std::ostream &stream) const override;
  };
}

#endif
