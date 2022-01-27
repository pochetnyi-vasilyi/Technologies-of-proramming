#include "rectangle.hpp"
#include <stdexcept>
#include <iostream>
#include <cmath>

pochetnyi::Rectangle::Rectangle(const point_t & center, double width, double height, double angle):
  center_(center),
  width_(width),
  height_(height),
  angle_(angle)
{
  if (height <= 0.0)
  {
    throw std::invalid_argument("Invalid height value!");
  }
  if (width <= 0.0)
  {
    throw std::invalid_argument("Invalid width value!");
  }
}

double pochetnyi::Rectangle::getArea() const
{
  return width_ * height_;
}

pochetnyi::rectangle_t pochetnyi::Rectangle::getFrameRect() const
{
  const double rads = angle_ * (M_PI / 180.0);
  const double width = height_ * fabs(sin(rads)) + width_ * fabs(cos(rads));
  const double height = height_ * fabs(cos(rads)) + width_ * fabs(sin(rads));
  return { width, height, center_ };
}

pochetnyi::point_t pochetnyi::Rectangle::getCenter() const
{
  return center_;
}

void pochetnyi::Rectangle::move(const point_t & point)
{
  center_ = point;
}

void pochetnyi::Rectangle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void pochetnyi::Rectangle::scale(double coef)
{
  if (coef <= 0.0) {
    throw std::invalid_argument("Invalid scaling coefficient value!");
  }
  width_ *= coef;
  height_ *= coef;
}

void pochetnyi::Rectangle::rotate(double degree)
{
  angle_ += degree;
}

void pochetnyi::Rectangle::printInfo() const
{
  std::cout << "Rectangle is " << width_ << " width, " << height_ << " height, has " << getArea() << " square.\n";
}
