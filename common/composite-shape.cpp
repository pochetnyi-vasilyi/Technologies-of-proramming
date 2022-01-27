#include "composite-shape.hpp"
#include <cmath>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include "base-types.hpp"
#include "shape.hpp"

pochetnyi::CompositeShape::CompositeShape() :
  list_(nullptr),
  count_(0)
{}

pochetnyi::CompositeShape::CompositeShape(const pochetnyi::CompositeShape &rhs) :
  list_(std::make_unique<SharedShapePtr[]>(rhs.count_)),
  count_(rhs.count_)
{
  for (size_t i = 0; i < count_; i++)
  {
    list_[i] = rhs.list_[i];
  }
}

pochetnyi::CompositeShape::CompositeShape(pochetnyi::CompositeShape &&rhs) :
  list_(nullptr),
  count_(0)
{
  *this = std::move(rhs);
}

pochetnyi::CompositeShape &pochetnyi::CompositeShape::operator=(const pochetnyi::CompositeShape &rhs)
{
  if (this == &rhs)
  {
    return *this;
  }
  list_ = std::make_unique<SharedShapePtr[]> (rhs.count_);
  count_ = rhs.count_;
  for (size_t i = 0; i < count_; ++i)
  {
    list_[i] = rhs.list_[i];
  }
  return *this;
}

pochetnyi::CompositeShape &pochetnyi::CompositeShape::operator=(pochetnyi::CompositeShape &&rhs)
{
  if (this == &rhs)
  {
    return *this;
  }
  count_ = rhs.count_;
  list_.swap(rhs.list_);
  rhs.list_ = nullptr;
  rhs.count_ = 0;
  return *this;
}

pochetnyi::CompositeShape::SharedShapePtr pochetnyi::CompositeShape::operator[](size_t index) const
{
  if (index >= count_)
  {
    throw std::out_of_range("Index out of range");
  }
  return list_[index];
}

double pochetnyi::CompositeShape::getArea() const
{
  double area = 0.0;
  for (size_t i = 0; i < count_; ++i)
  {
    area += list_[i]->getArea();
  }
  return area;
}

pochetnyi::point_t pochetnyi::CompositeShape::getCenter() const
{
  return getFrameRect().pos;
}

pochetnyi::rectangle_t pochetnyi::CompositeShape::getFrameRect() const
{
  if (count_ == 0)
  {
    return {-1.0, -1.0, {0.0, 0.0}};
  }
  pochetnyi::rectangle_t frameRect = list_[0]->getFrameRect();
  size_t i = 0;
  for (; i < count_; i++)
  {
    if ((frameRect.width != -1.0) && (frameRect.height != -1.0))
    {
      frameRect = list_[i]->getFrameRect();
      break;
    }
  }
  double minLeft = frameRect.pos.x - frameRect.width / 2.0;
  double maxRight = frameRect.pos.x + frameRect.width / 2.0;
  double maxTop = frameRect.pos.y + frameRect.height / 2.0;
  double minBottom = frameRect.pos.y - frameRect.height / 2.0;

  for (; i < count_; i++)
  {
    pochetnyi::rectangle_t currentFrameRect = list_[i]->getFrameRect();
    if ((currentFrameRect.width == -1.0) && (currentFrameRect.height == -1.0))
    {
      continue;
    }
    double left = currentFrameRect.pos.x - currentFrameRect.width / 2.0;
    double right = currentFrameRect.pos.x + currentFrameRect.width / 2.0;
    double top = currentFrameRect.pos.y + currentFrameRect.height / 2.0;
    double bottom = currentFrameRect.pos.y - currentFrameRect.height / 2.0;
    minLeft = std::min(left, minLeft);
    maxRight = std::max(right, maxRight);
    maxTop = std::max(top, maxTop);
    minBottom = std::min(bottom, minBottom);
  }
  double width = maxRight - minLeft;
  double height = maxTop - minBottom;
  return {width, height, {(minLeft + width / 2.0), (minBottom + height / 2.0)}};
}

void pochetnyi::CompositeShape::move(const pochetnyi::point_t &point)
{
  const pochetnyi::point_t newPoint = getFrameRect().pos;
  move(point.x - newPoint.x, point.y - newPoint.y);
}

void pochetnyi::CompositeShape::move(double dx, double dy)
{
  for (size_t i = 0; i < count_; i++)
  {
    list_[i]->move(dx, dy);
  }
}

void pochetnyi::CompositeShape::scale(double coef)
{
  if (coef <= 0.0)
  {
    throw std::invalid_argument("Invalid scaling coefficient value!");
  }
  const pochetnyi::point_t center = getFrameRect().pos;
  for (size_t i = 0; i < count_; i++)
  {
    const pochetnyi::point_t curPos = list_[i]->getFrameRect().pos;
    list_[i]->move({center.x + coef * (curPos.x - center.x), center.y - coef * (curPos.y - center.y)});
    list_[i]->scale(coef);
  }
}

void pochetnyi::CompositeShape::rotate(double degrees)
{
  const double rads = degrees * (M_PI / 180.0);
  const double sinX = sin(rads);
  const double cosX = cos(rads);
  const double cx = getCenter().x;
  const double cy = getCenter().y;
  for (size_t i = 0; i < count_; i++)
  {
    const pochetnyi::point_t curPos = list_[i]->getCenter();
    const double posX = (curPos.x - cx) * cosX - (curPos.y - cy) * sinX + cx;
    const double posY = (curPos.y - cy) * cosX + (curPos.x - cx) * sinX + cy;
    list_[i]->move({ posX, posY });
    list_[i]->rotate(degrees);
  }
}

size_t pochetnyi::CompositeShape::getCount() const
{
  return count_;
}

void pochetnyi::CompositeShape::printInfo() const
{
  if (count_ == 0)
  {
    throw std::length_error("List is empty!");
  }
  for (size_t i = 0; i < count_; i++)
  {
    std::cout << i + 1 << ": ";
    list_[i]->printInfo();
  }
}

void pochetnyi::CompositeShape::addShape(SharedShapePtr &rhs)
{
  if (!rhs)
  {
    throw std::invalid_argument("Invalid shape pointer!");
  }
  std::unique_ptr<SharedShapePtr[]> temp = std::make_unique<SharedShapePtr[]>(count_ + 1);
  for (size_t i = 0; i < count_; ++i)
  {
    temp[i] = list_[i];
  }
  temp[count_] = rhs;
  count_++;
  list_.swap(temp);
}

void pochetnyi::CompositeShape::removeShape(size_t index)
{
  if (count_ == 0)
  {
    throw std::out_of_range("List is empty!");
  }
  if (count_ <= index)
  {
    throw std::out_of_range("Index out of range!");
  }
  if ((count_ == 1) && (index == 0))
  {
    clearList();
    return;
  }
  std::unique_ptr<SharedShapePtr[]> temp = std::make_unique<SharedShapePtr[]>(count_ - 1);
  for (size_t i = 0; i < index; ++i)
  {
    temp[i] = list_[i];
  }
  for (size_t i = index; i < count_ - 1; ++i)
  {
    temp[i] = list_[i + 1];
  }
  list_.swap(temp);
  count_--;
}

void pochetnyi::CompositeShape::clearList()
{
  list_.reset();
  list_ = nullptr;
  count_ = 0;
}
