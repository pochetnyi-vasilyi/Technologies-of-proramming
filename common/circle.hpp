#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "base-types.hpp"
#include "shape.hpp"

namespace pochetnyi
{
  class Circle : public Shape
  {
  public:
    Circle(const point_t & center, double radius);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t & point) override;
    void move(double dx, double dy) override;
    void scale(double coef) override;
    void rotate(double degree) override;
    point_t getCenter() const override;
    double getRadius() const;

    void printInfo() const override;

  private:
    point_t center_;
    double radius_;
  };
}

#endif
