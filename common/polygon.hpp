#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <initializer_list>
#include <memory>
#include "shape.hpp"

namespace pochetnyi
{
  class Polygon : public Shape
  {
  public:
    Polygon(const std::initializer_list<point_t> &points);
    Polygon(const Polygon &rhs);
    Polygon(Polygon &&rhs);

    Polygon &operator=(const Polygon &rhs);
    Polygon &operator=(Polygon &&rhs);
    point_t operator[](size_t index) const;

    size_t getCount() const;
    rectangle_t getFrameRect() const override;
    double getArea() const override;
    point_t getCenter() const override;

    void move(double dx, double dy) override;
    void move(const point_t &point) override;
    void scale(double coef) override;
    void rotate(double degree) override;
    void printInfo() const override;

  private:
    size_t count_;
    std::unique_ptr<point_t[]> vertexes_;
  };
}

#endif
