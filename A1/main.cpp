#include <iostream>
#include <stdexcept>
#include "shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"
#include "base-types.hpp"

void printCenterInfo(Shape*);
void printFrameRectInfo(Shape*);
void printInfoMoveToPoint(Shape*, const point_t&);
void printInfoMoveByDelta(Shape*, const double, const double);

int main()
{
  std::cout << "Rectangle:\n";
  Shape *p = nullptr;
  try
  {
    p = new Rectangle({ 0.0, 0.0 }, 10.0, 20.0);
  }
  catch (std::invalid_argument& error)
  {
    std::cerr << error.what();
    return 1;
  }
  point_t point{ 18.0, 22.0 };
  p -> printInfo();
  printFrameRectInfo(p);
  p -> move(point);
  printInfoMoveToPoint(p, point);
  p -> move(point.x, point.y);
  printInfoMoveByDelta(p, point.x, point.y);
  delete p;

  std::cout << "\nCircle:\n";
  try
  {
    p = new Circle({ 1.0, 1.0 }, 10.0);
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
  delete p;

  std::cout << "\nTriangle:\n";
  try
  {
    p = new Triangle( { 0.0, 0.0 }, { 1.0, 0.0 }, { 0.0, 1.0 } );
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
  delete p;
  
  return 0;
}

void printCenterInfo(Shape* p)
{
  std::cout << "Center coordinates are in (" << p -> getCenter().x << ", " << p -> getCenter().y << ").\n";
}

void printFrameRectInfo(Shape* p)
{
  std::cout << "Frame rectangle is " << p -> getFrameRect().height << " height, " << p -> getFrameRect().width
      << " width, it's center is (" << p -> getFrameRect().pos.x << ", " << p -> getFrameRect().pos.y << ").\n";
}

void printInfoMoveToPoint(Shape* p, const point_t& point)
{
  std::cout << "After moving to point(" << point.x << ", " << point.y << "):\n";
  p -> printInfo();
  printCenterInfo(p);
}

void printInfoMoveByDelta(Shape* p, const double dx, const double dy)
{
  std::cout << "After moving by " << dx << ", " << dy << ":\n";
  p -> printInfo();
  printCenterInfo(p);
}
