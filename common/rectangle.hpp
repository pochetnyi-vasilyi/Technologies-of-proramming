#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "base-types.hpp"
#include "shape.hpp"

namespace pochetnyi
{
  class Rectangle : public Shape
  {
  public:
    Rectangle(const point_t & center, double width, double height, double angle = 0.0);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t & point) override;
    void move(double dx, double dy) override;
    void scale(double coef) override;
    void rotate(double degree) override;
    point_t getCenter() const override;

    void printInfo() const override;

  private:
    point_t center_;
    double width_;
    double height_;
    double angle_;
 };
}

#endif
