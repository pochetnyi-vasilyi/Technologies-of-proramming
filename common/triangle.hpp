#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "base-types.hpp"
#include "shape.hpp"

namespace pochetnyi
{
  class Triangle : public Shape
  {
  public:
    Triangle(const point_t & a, const point_t & b, const point_t & c, double angle = 0.0);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t & point) override;
    void move(double dx, double dy) override;
    point_t getCenter() const override;
    double getLength(const point_t a, const point_t b) const;
    void scale(double coef) override;
    void rotate(double degree) override;

    void printInfo() const override;

  private:
    point_t a_;
    point_t b_;
    point_t c_;
    double angle_;
  };
}

#endif
