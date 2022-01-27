#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "shape.hpp"

namespace pochetnyi
{
  class Square : public Shape
  {
  public:
    Square(Point point);

    std::ostream &draw(std::ostream &stream) const override;
  };
}

#endif
