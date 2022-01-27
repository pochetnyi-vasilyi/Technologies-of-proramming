#include "circle.hpp"
#include <cmath>
#include <stdexcept>
#include <iostream>

pochetnyi::Circle::Circle(const point_t & center, double radius):
  center_(center),
  radius_(radius)
{
  if (radius <= 0.0)
  {
    throw std::invalid_argument("Invalid radius value!");
  }
}

double pochetnyi::Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

pochetnyi::rectangle_t pochetnyi::Circle::getFrameRect() const
{
  return { radius_ * 2, radius_ * 2, center_ };
}

pochetnyi::point_t pochetnyi::Circle::getCenter() const
{
  return center_;
}

double pochetnyi::Circle::getRadius() const
{
  return radius_;
}

void pochetnyi::Circle::move(const point_t & point)
{
  center_ = point;
}

void pochetnyi::Circle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void pochetnyi::Circle::scale(double coef)
{
  if (coef <= 0.0) {
    throw std::invalid_argument("Invalid scaling coefficient value!");
  }
  radius_ *= coef;
}

void pochetnyi::Circle::rotate(double)
{}

void pochetnyi::Circle::printInfo() const
{
  std::cout << "Circle radius is " << radius_ << " it has " << getArea() << " square.\n";
}
