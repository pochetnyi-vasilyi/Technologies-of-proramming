#include "triangle.hpp"
#include <algorithm>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <cmath>

Triangle::Triangle(const point_t & a, const point_t & b, const point_t & c):
  a_(a),
  b_(b),
  c_(c)
{
  double ab = getLength(a_, b_);
  double bc = getLength(b_, c_);
  double ac = getLength(a_, c_);
  if (((ab + ac) == bc) || ((ab + bc) == ac) || ((ac + bc) == ab))
  {
    throw std::invalid_argument("Sum of 2 sides of triangle equals remaining side!\n");
  }
}

double Triangle::getArea() const
{
  double ab = getLength(a_, b_);
  double bc = getLength(b_, c_);
  double ac = getLength(a_, c_);
  double halfPer = (ab + bc + ac) / 2.0;
  return sqrt(halfPer * (halfPer - ab) * (halfPer - bc) * (halfPer - ac));
}

double Triangle::getLength(const point_t a, const point_t b)
{
  return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

point_t Triangle::getCenter() const
{
  double cx = (a_.x + b_.x + c_.x) / 3.0;
  double cy = (a_.y + b_.y + c_.y) / 3.0;
  return { cx, cy };
}

rectangle_t Triangle::getFrameRect() const
{
  double width = std::max(std::max(a_.x, b_.x), c_.x) - std::min(std::min(a_.x, b_.x), c_.x);
  double height = std::max(std::max(a_.y, b_.y), c_.y) - std::min(std::min(a_.y, b_.y), c_.y);
  return { width, height, getCenter() };
}

void Triangle::move(const double dx, const double dy)
{
  a_.x += dx;
  b_.x += dx;
  c_.x += dx;
  a_.y += dy;
  b_.y += dy;
  c_.y += dy;
}

void Triangle::move(const point_t & point)
{
  move(point.x - getCenter().x, point.y - getCenter().y);
}

void Triangle::printInfo() const
{
  std::cout << "Triangle vertexes are (" << a_.x << ", " << a_.y << "), (" << b_.x << ", " << b_.y << ") and ("
      << c_.x << ", " << c_.y << "), it has " << getArea() << " square.\n";
}
