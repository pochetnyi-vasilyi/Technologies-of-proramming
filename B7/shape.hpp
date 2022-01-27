#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <iosfwd>
#include "../common/point.hpp"

namespace pochetnyi
{
  class Shape
  {
  public:
    Shape(Point &point);
    virtual ~Shape() = default;

    bool isMoreLeft(const Shape &shape) const;
    bool isUpper(const Shape &shape) const;
    virtual std::ostream &draw(std::ostream &stream) const = 0;
    friend std::ostream &operator<<(std::ostream &stream, const Shape &shape);

  protected:
    Point center_;
  };
}

#endif
