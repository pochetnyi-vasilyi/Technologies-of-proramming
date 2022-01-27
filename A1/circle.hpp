#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "base-types.hpp"
#include "shape.hpp"

class Circle : public Shape
{
public:
  Circle(const point_t & center, const double radius);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t & point) override;
  void move(const double dx, const double dy) override;
  point_t getCenter() const override;
  
  void printInfo() const override;

private:
  point_t center_;
  double radius_;
};

#endif
