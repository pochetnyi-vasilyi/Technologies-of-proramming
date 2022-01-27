#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <memory>

namespace pochetnyi
{
  struct point_t;
  struct rectangle_t;

  class Shape
  {
  public:
    using SharedShapePtr = std::shared_ptr<Shape>;

    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(const point_t & point) = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void scale(double coef) = 0;
    virtual void rotate(double degree) = 0;
    virtual point_t getCenter() const = 0;
    virtual void printInfo() const = 0;
  };
}

#endif
