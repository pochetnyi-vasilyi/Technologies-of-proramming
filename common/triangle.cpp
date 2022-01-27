#include "triangle.hpp"
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <cmath>

pochetnyi::Triangle::Triangle(const point_t & a, const point_t & b, const point_t & c, double angle):
  a_(a),
  b_(b),
  c_(c),
  angle_(angle)
{
  double ab = getLength(a_, b_);
  double bc = getLength(b_, c_);
  double ac = getLength(a_, c_);
  if (((ab + ac) == bc) || ((ab + bc) == ac) || ((ac + bc) == ab))
  {
    throw std::invalid_argument("Sum of 2 sides of triangle equals remaining side!\n");
  }
}

double pochetnyi::Triangle::getArea() const
{
  double ab = getLength(a_, b_);
  double bc = getLength(b_, c_);
  double ac = getLength(a_, c_);
  double halfPer = (ab + bc + ac) / 2.0;
  return sqrt(halfPer * (halfPer - ab) * (halfPer - bc) * (halfPer - ac));
}

double pochetnyi::Triangle::getLength(const point_t a, const point_t b) const
{
  return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

pochetnyi::point_t pochetnyi::Triangle::getCenter() const
{
  double cx = (a_.x + b_.x + c_.x) / 3.0;
  double cy = (a_.y + b_.y + c_.y) / 3.0;
  return { cx, cy };
}

pochetnyi::rectangle_t pochetnyi::Triangle::getFrameRect() const
{
  double width = std::max({a_.x, b_.x, c_.x}) - std::min({a_.x, b_.x, c_.x});
  double height = std::max({a_.y, b_.y, c_.y}) - std::min({a_.y, b_.y, c_.y});
  return { width, height, getCenter() };
}

void pochetnyi::Triangle::move(double dx, double dy)
{
  a_.x += dx;
  b_.x += dx;
  c_.x += dx;
  a_.y += dy;
  b_.y += dy;
  c_.y += dy;
}

void pochetnyi::Triangle::move(const point_t & point)
{
  move(point.x - getCenter().x, point.y - getCenter().y);
}

void pochetnyi::Triangle::scale(double coef)
{
  if (coef <= 0.0)
  {
    throw std::invalid_argument("Invalid scaling coefficient value!");
  }
  double cx = getCenter().x;
  double cy = getCenter().y;
  a_.x = cx + ((a_.x - cx) * coef);
  a_.y = cy + ((a_.y - cy) * coef);
  b_.x = cx + ((b_.x - cx) * coef);
  b_.y = cy + ((b_.y - cy) * coef);
  c_.x = cx + ((c_.x - cx) * coef);
  c_.y = cy + ((c_.y - cy) * coef);
}

void pochetnyi::Triangle::rotate(double degree)
{
  angle_ += degree;
  const double rads = angle_ * (M_PI / 180.0);
  const double sinX = sin(rads);
  const double cosX = cos(rads);
  const double cx = getCenter().x;
  const double cy = getCenter().y;
  a_ = { (a_.x - cx) * cosX - (a_.y - cy) * sinX + cx, (a_.x - cx) * sinX - (a_.y - cy) * cosX + cy };
  b_ = { (b_.x - cx) * cosX - (b_.y - cy) * sinX + cx, (b_.x - cx) * sinX - (b_.y - cy) * cosX + cy };
  c_ = { (c_.x - cx) * cosX - (c_.y - cy) * sinX + cx, (c_.x - cx) * sinX - (c_.y - cy) * cosX + cy };
}

void pochetnyi::Triangle::printInfo() const
{
  std::cout << "Triangle vertexes are (" << a_.x << ", " << a_.y << "), (" << b_.x << ", " << b_.y << ") and ("
      << c_.x << ", " << c_.y << "), it has " << getArea() << " square.\n";
}
