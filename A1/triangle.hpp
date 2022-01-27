#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "base-types.hpp"
#include "shape.hpp"

class Triangle : public Shape
{
public:
  Triangle(const point_t & a, const point_t & b, const point_t & c);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t & point) override;
  void move(const double dx, const double dy) override;
  point_t getCenter() const override;

  void printInfo() const override;

private:
  point_t a_;
  point_t b_;
  point_t c_;

  static double getLength(const point_t a, const point_t b);
};

#endif
