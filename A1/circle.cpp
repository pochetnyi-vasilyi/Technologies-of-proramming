#include "circle.hpp"
#include <iostream>
#include <cmath>
#include <stdexcept>

Circle::Circle(const point_t & center, const double radius) :
  center_(center),
  radius_(radius)
{
  if (radius <= 0.0)
  {
    throw std::invalid_argument("Invalid radius!\n");
  }
}

double Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const
{
  return { radius_ * 2, radius_ * 2, center_ };
}

void Circle::move(const point_t & point)
{
  center_ = point;
}

void Circle::move(const double dx, const double dy)
{
  center_.x += dx;
  center_.y += dy;
}

point_t Circle::getCenter() const
{
  return center_;
}

void Circle::printInfo() const
{
  std::cout << "Circle radius is " << radius_ << " it has " << getArea() << " square.\n";
}
