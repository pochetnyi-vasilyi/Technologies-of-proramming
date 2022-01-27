#include <iostream>
#include <stdexcept>
#include <memory>
#include "../common/shape.hpp"
#include "../common/rectangle.hpp"
#include "../common/circle.hpp"
#include "../common/triangle.hpp"
#include "../common/base-types.hpp"
#include "../common/composite-shape.hpp"
#include "../common/matrix.hpp"
#include "../common/polygon.hpp"

void printCenterInfo(pochetnyi::Shape&);
void printFrameRectInfo(pochetnyi::Shape&);
void printInfoMoveToPoint(pochetnyi::Shape&, const pochetnyi::point_t&);
void printInfoMoveByDelta(pochetnyi::Shape&, double, double);
void printScalingInfo(pochetnyi::Shape&, double);
void printRotatingInfo(pochetnyi::Shape&, double);

int main()
{
  std::cout << "Rectangle:\n";
  std::shared_ptr<pochetnyi::Shape> p = nullptr;
  try
  {
    p = std::make_shared<pochetnyi::Rectangle>(pochetnyi::point_t{ 0.0, 0.0 }, 10.0, 20.0);
  }
  catch (const std::invalid_argument& error)
  {
    std::cerr << error.what();
    return 1;
  }
  pochetnyi::point_t point{ 18.0, 22.0 };
  p -> printInfo();
  printFrameRectInfo(*p);
  p -> move(point);
  printInfoMoveToPoint(*p, point);
  p -> move(point.x, point.y);
  printInfoMoveByDelta(*p, point.x, point.y);
  double coef = 5.0;
  try
  {
    p -> scale(coef);
  }
  catch (const std::invalid_argument& error)
  {
    std::cerr << error.what();
    return 1;
  }
  printScalingInfo(*p, coef);
  double degrees = 127.0;
  p -> rotate(degrees);
  printRotatingInfo(*p, degrees);
  std::shared_ptr<pochetnyi::CompositeShape> cShape = nullptr;
  std::unique_ptr<pochetnyi::Matrix> matrix = nullptr;
  try
  {
    cShape->addShape(p);
    matrix->addShape(p);
  }
  catch (const std::invalid_argument& error)
  {
    std::cerr << error.what();
    return 1;
  }

  std::cout << "\nCircle:\n";
  try
  {
    p = std::make_shared<pochetnyi::Circle>(pochetnyi::point_t{ 1.0, 1.0 }, 10.0);
  }
  catch (const std::invalid_argument& error)
  {
    std::cerr << error.what();
    return 1;
  }
  point = { 2.0, 2.0 };
  p -> printInfo();
  printFrameRectInfo(*p);
  p -> move(point);
  printInfoMoveToPoint(*p, point);
  p -> move(point.x, point.y);
  printInfoMoveByDelta(*p, point.x, point.y);
  coef = 3.5;
  try
  {
    p -> scale(coef);
  }
  catch (const std::invalid_argument& error)
  {
    std::cerr << error.what();
    return 1;
  }
  printScalingInfo(*p, coef);
  degrees = 30.0;
  p -> rotate(degrees);
  printRotatingInfo(*p, degrees);
  try
  {
    cShape->addShape(p);
    matrix->addShape(p);
  }
  catch (const std::invalid_argument& error)
  {
    std::cerr << error.what();
    return 1;
  }

  std::cout << "\nTriangle:\n";
  try
  {
    p = std::make_shared<pochetnyi::Triangle>(pochetnyi::point_t{ 0.0, 0.0 },
        pochetnyi::point_t{ 1.0, 0.0 }, pochetnyi::point_t{ 0.0, 1.0 });
  }
  catch (const std::invalid_argument& error)
  {
    std::cerr << error.what();
    return 1;
  }
  point = { 12.0, 8.0 };
  p -> printInfo();
  printFrameRectInfo(*p);
  p -> move(point);
  printInfoMoveToPoint(*p, point);
  p -> move(point.x, point.y);
  printInfoMoveByDelta(*p, point.x, point.y);
  coef = 4.22;
  try
  {
    p -> scale(coef);
  }
  catch (const std::invalid_argument& error)
  {
    std::cerr << error.what();
    return 1;
  }
  printScalingInfo(*p, coef);
  degrees = 410.0;
  p -> rotate(degrees);
  printRotatingInfo(*p, degrees);
  try
  {
    cShape->addShape(p);
    matrix->addShape(p);
  }
  catch (const std::invalid_argument& error)
  {
    std::cerr << error.what();
    return 1;
  }
  
  std::cout << "\nComposite shape:\n";
  try
  {
    cShape->printInfo();
  }
  catch (const std::length_error& error)
  {
    std::cerr << error.what();
    return 1;
  }
  printFrameRectInfo(*cShape);
  point = { 12.0, 8.0 };
  cShape -> move(point);
  printInfoMoveToPoint(*cShape, point);
  cShape -> move(point.x, point.y);
  printInfoMoveByDelta(*cShape, point.x, point.y);
  coef = 7.1;
  try
  {
    cShape->scale(coef);
  }
  catch (const std::invalid_argument& error)
  {
    std::cerr << error.what();
    return 1;
  }
  printScalingInfo(*cShape, coef);
  degrees = 42.0;
  cShape -> rotate(degrees);
  printRotatingInfo(*cShape, degrees);
  try
  {
    matrix->addShape(cShape);
  }
  catch (const std::invalid_argument& error)
  {
    std::cerr << error.what();
    return 1;
  }

  std::cout << "\nMatrix:\n";
  matrix->printInfo();

  std::cout << "\nPolygon:\n";
  std::initializer_list<pochetnyi::point_t> points = { { 7.16,  55.3 }, { 18.9,  11.1 }, { -25.8, 66.02 },
      { 13.54,  -24.38 } };
  try
  {
    p = std::make_unique<pochetnyi::Polygon>(points);
  }
  catch (const std::invalid_argument &error)
  {
    std::cerr << error.what();
    return 1;
  }
  point = { 2.0, 2.0 };
  p->printInfo();
  printFrameRectInfo(*p);
  p->move(point);
  printInfoMoveToPoint(*p, point);
  p->move(point.x, point.y);
  printInfoMoveByDelta(*p, point.x, point.y);
  coef = 3.5;
  try
  {
    p->scale(coef);
  }
  catch (const std::invalid_argument& error)
  {
    std::cerr << error.what();
    return 1;
  }
  printScalingInfo(*p, coef);
  degrees = 300.0;
  p->rotate(degrees);
  printRotatingInfo(*p, degrees);

  return 0;
}

void printCenterInfo(pochetnyi::Shape& p)
{
  std::cout << "Center coordinates are in (" << p.getCenter().x << ", " << p.getCenter().y << ").\n";
}

void printFrameRectInfo(pochetnyi::Shape& p)
{
  std::cout << "Frame rectangle is " << p.getFrameRect().height << " height, " << p.getFrameRect().width
      << " width, it's center is (" << p.getFrameRect().pos.x << ", " << p.getFrameRect().pos.y << ").\n";
}

void printInfoMoveToPoint(pochetnyi::Shape& p, const pochetnyi::point_t& point)
{
  std::cout << "After moving to point(" << point.x << ", " << point.y << "):\n";
  p.printInfo();
  printCenterInfo(p);
}

void printInfoMoveByDelta(pochetnyi::Shape& p, double dx, double dy)
{
  std::cout << "After moving by " << dx << ", " << dy << ":\n";
  p.printInfo();
  printCenterInfo(p);
}

void printScalingInfo(pochetnyi::Shape& p, double coef)
{
  std::cout << "After scaling in " << coef << " times:\n";
  p.printInfo();
  printCenterInfo(p);
  printFrameRectInfo(p);
}

void printRotatingInfo(pochetnyi::Shape& p, double degree)
{
  std::cout << "After rotating on " << degree << " degrees:\n";
  p.printInfo();
  printCenterInfo(p);
  printFrameRectInfo(p);
}
