#include "polygon.hpp"
#include <memory>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <initializer_list>
#include "base-types.hpp"

pochetnyi::Polygon::Polygon(const std::initializer_list<point_t> &points) :
  count_(points.size()),
  vertexes_(nullptr)
{
  if (points.size() < 3)
  {
    throw (std::invalid_argument("Polygon must have at least 3 vertexes!"));
  }
  vertexes_ = std::make_unique<point_t[]>(count_);
  size_t i = 0;
  for (std::initializer_list<point_t>::const_iterator vertex = points.begin(); vertex != points.end(); vertex++)
  {
    vertexes_[i] = *vertex;
    i++;
  }
  if (getArea() == 0.0)
  {
    throw(std::invalid_argument("Invalid area value!"));
  }
}

pochetnyi::Polygon::Polygon(const Polygon &rhs) :
  count_(rhs.count_),
  vertexes_(std::make_unique<point_t[]>(count_))
{
  for (size_t i = 0; i < count_; i++)
  {
    vertexes_[i] = rhs.vertexes_[i];
  }
}

pochetnyi::Polygon::Polygon(Polygon &&rhs) :
  count_(0),
  vertexes_(nullptr)
{
  *this = std::move(rhs);
}

pochetnyi::Polygon &pochetnyi::Polygon::operator=(const Polygon &rhs)
{
  if (this == &rhs)
  {
    return *this;
  }
  count_ = rhs.count_;
  vertexes_ = std::make_unique<point_t[]>(rhs.count_);
  for (size_t i = 0; i < count_; i++)
  {
    vertexes_[i] = rhs.vertexes_[i];
  }
  return *this;
}

pochetnyi::Polygon &pochetnyi::Polygon::operator=(Polygon &&rhs)
{
  if (this == &rhs)
  {
    return *this;
  }
  count_ = std::move(rhs.count_);
  vertexes_ = std::move(rhs.vertexes_);
  return *this;
}

pochetnyi::point_t pochetnyi::Polygon::operator[](size_t index) const
{
  if (index >= count_)
  {
    throw (std::out_of_range ("Index is out of range!"));
  }
  return (vertexes_[index]);
}

size_t pochetnyi::Polygon::getCount() const
{
  return count_;
}

pochetnyi::point_t pochetnyi::Polygon::getCenter() const
{
  pochetnyi::point_t center = {0.0, 0.0};
  for (size_t i = 0; i < count_; i++)
  {
    center.x += vertexes_[i].x;
    center.y += vertexes_[i].y;
  }
  center.x /= count_;
  center.y /= count_;
  return center;
}

pochetnyi::rectangle_t pochetnyi::Polygon::getFrameRect() const
{
  double maxX = vertexes_[0].x;
  double maxY = vertexes_[0].y;
  double minX = maxX;
  double minY = maxY;
  for (size_t i = 1; i < count_; i++)
  {
    maxX = std::max(maxX, vertexes_[i].x);
    maxY = std::max(maxY, vertexes_[i].y);
    minX = std::min(minX, vertexes_[i].x);
    minY = std::min(minY, vertexes_[i].y);
  }
  pochetnyi::rectangle_t frameRect;
  frameRect.pos = { (maxX + minX) / 2.0, (maxY + minY) / 2.0 };
  frameRect.height = maxY - minY;
  frameRect.width = maxX - minX;
  return frameRect;
}

double pochetnyi::Polygon::getArea() const
{
  const double cx = getCenter().x;
  const double cy = getCenter().y;
  const double dxFirst = vertexes_[0].x - cx;
  const double dyFirst = vertexes_[0].y - cy;
  const double dxLast = vertexes_[count_ - 1].x - cx;
  const double dyLast = vertexes_[count_ - 1].y - cy;
  double area = (dxLast * dyFirst - dxFirst * dyLast) / 2.0;
  for (size_t i = 0; i < count_ - 1; i++)
  {
    double dx = vertexes_[i].x - cx;
    double dy = vertexes_[i].y - cy;
    double dxNext = vertexes_[i + 1].x - cx;
    double dyNext = vertexes_[i + 1].y - cy;
    area += (dx * dyNext - dxNext * dy) / 2.0;
  }
  return fabs(area);
}

void pochetnyi::Polygon::move(double dx, double dy)
{
  for (size_t i = 0; i < count_; i++)
  {
    vertexes_[i].x += dx;
    vertexes_[i].y += dy;
  }
}

void pochetnyi::Polygon::move(const point_t &point)
{
  const double cx = getCenter().x;
  const double cy = getCenter().y;
  move (point.x - cx, point.y - cy);
}

void pochetnyi::Polygon::scale(double coef)
{
  if (coef <= 0.0)
  {
    throw (std::invalid_argument("Invalid scaling coefficient value!"));
  }
  const double cx = getCenter().x;
  const double cy = getCenter().y;
  for (size_t i = 0; i < count_; i++)
  {
    vertexes_[i].x = cx + ((vertexes_[i].x - cx) * coef);
    vertexes_[i].y = cy + ((vertexes_[i].y - cy) * coef);
  }
}

void pochetnyi::Polygon::rotate(double degree)
{
  const double rads = degree * (M_PI / 180.0);
  const double sinX = sin(rads);
  const double cosX = cos(rads);
  const double cx = getCenter().x;
  const double cy = getCenter().y;
  for (size_t i = 0; i < count_; i++)
  {
    const double vx = vertexes_[i].x;
    const double vy = vertexes_[i].y;
    vertexes_[i].x = cx + cosX * (vx - cx) - sinX * (vy - cy);
    vertexes_[i].y = cy + cosX * (vy - cy) + sinX * (vx - cx);
  }
}

void pochetnyi::Polygon::printInfo() const
{
  std::cout << "Polygon vertexes are: (";
  for (size_t i = 0; i < count_; i++)
  {
    std::cout << vertexes_[i].x << ", " << vertexes_[i].y;
    if (i != count_ - 1)
    {
      std::cout << "); (";
    }
  }
  std::cout << ").\nIt has " << getArea() << " square.\n";
}
