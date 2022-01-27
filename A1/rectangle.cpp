#include "rectangle.hpp"
#include <iostream>
#include <stdexcept>

Rectangle::Rectangle(const point_t & center, const double width, const double height) :
  center_(center),
  width_(width),
  height_(height)
{
  if (height <= 0.0)
  {
    throw std::invalid_argument("Invalid height! It must be more than 0.\n");
  }
  if (width <= 0.0)
  {
    throw std::invalid_argument("Invalid width! It must be more than 0.\n");
  }
}

double Rectangle::getArea() const
{
  return width_ * height_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return { width_, height_, center_ };
}

void Rectangle::move(const point_t & point)
{
  center_ = point;
}

void Rectangle::move(const double dx, const double dy)
{
  center_.x += dx;
  center_.y += dy;
}

point_t Rectangle::getCenter() const
{
  return center_;
}

void Rectangle::printInfo() const
{
  std::cout << "Rectangle is " << width_ << " width, " << height_ << " height, has " << getArea() << " square.\n";
}
