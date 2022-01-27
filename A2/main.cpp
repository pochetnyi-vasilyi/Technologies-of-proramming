#include <iostream>
#include <stdexcept>
#include "../common/shape.hpp"
#include "../common/rectangle.hpp"
#include "../common/circle.hpp"
#include "../common/triangle.hpp"
#include "../common/base-types.hpp"

void printCenterInfo(pochetnyi::Shape*);
void printFrameRectInfo(pochetnyi::Shape*);
void printInfoMoveToPoint(pochetnyi::Shape*, const pochetnyi::point_t&);
void printInfoMoveByDelta(pochetnyi::Shape*, const double, const double);
void printScalingInfo(pochetnyi::Shape*, const double);

int main()
{
  std::cout << "Rectangle:\n";
  pochetnyi::Shape *p = nullptr;
  try
  {
    p = new pochetnyi::Rectangle({ 0.0, 0.0 }, 10.0, 20.0);
  }
  catch (std::invalid_argument& error)
  {
    std::cerr << error.what();
    return 1;
  }
  pochetnyi::point_t point{ 18.0, 22.0 };
  p -> printInfo();
  printFrameRectInfo(p);
  p -> move(point);
  printInfoMoveToPoint(p, point);
  p -> move(point.x, point.y);
  printInfoMoveByDelta(p, point.x, point.y);
  double coef = 5.0;
  try
  {
    p -> scale(coef);
  }
  catch (std::invalid_argument& error)
  {
    std::cerr << error.what();
    delete p;
    return 1;
  }
  printScalingInfo(p, coef);
  delete p;

  std::cout << "\nCircle:\n";
  try
  {
    p = new pochetnyi::Circle({ 1.0, 1.0 }, 10.0);
  }
  catch (std::invalid_argument& error)
  {
    std::cerr << error.what();
    return 1;
  }
  point = { 2.0, 2.0 };
  p -> printInfo();
  printFrameRectInfo(p);
  p -> move(point);
  printInfoMoveToPoint(p, point);
  p -> move(point.x, point.y);
  printInfoMoveByDelta(p, point.x, point.y);
  coef = 3.5;
  try
  {
    p -> scale(coef);
  }
  catch (std::invalid_argument& error)
  {
    std::cerr << error.what();
    delete p;
    return 1;
  }
  printScalingInfo(p, coef);
  delete p;

  std::cout << "\nTriangle:\n";
  try
  {
    p = new pochetnyi::Triangle({ 0.0, 0.0 }, { 1.0, 0.0 }, { 0.0, 1.0 });
  }
  catch (std::invalid_argument& error)
  {
    std::cerr << error.what();
    return 1;
  }
  point = { 12.0, 8.0 };
  p -> printInfo();
  printFrameRectInfo(p);
  p -> move(point);
  printInfoMoveToPoint(p, point);
  p -> move(point.x, point.y);
  printInfoMoveByDelta(p, point.x, point.y);
  coef = 4.22;
  try
  {
    p -> scale(coef);
  }
  catch (std::invalid_argument& error)
  {
    std::cerr << error.what();
    delete p;
    return 1;
  }
  printScalingInfo(p, coef);
  delete p;
  
  return 0;
}

void printCenterInfo(pochetnyi::Shape* p)
{
  std::cout << "Center coordinates are in (" << p -> getCenter().x << ", " << p -> getCenter().y << ").\n";
}

void printFrameRectInfo(pochetnyi::Shape* p)
{
  std::cout << "Frame rectangle is " << p -> getFrameRect().height << " height, " << p -> getFrameRect().width
      << " width, it's center is (" << p -> getFrameRect().pos.x << ", " << p -> getFrameRect().pos.y << ").\n";
}

void printInfoMoveToPoint(pochetnyi::Shape* p, const pochetnyi::point_t& point)
{
  std::cout << "After moving to point(" << point.x << ", " << point.y << "):\n";
  p -> printInfo();
  printCenterInfo(p);
}

void printInfoMoveByDelta(pochetnyi::Shape* p, const double dx, const double dy)
{
  std::cout << "After moving by " << dx << ", " << dy << ":\n";
  p -> printInfo();
  printCenterInfo(p);
}

void printScalingInfo(pochetnyi::Shape* p, const double coef)
{
  std::cout << "After scaling in " << coef << " times:\n";
  p -> printInfo();
  printCenterInfo(p);
  printFrameRectInfo(p);
}
