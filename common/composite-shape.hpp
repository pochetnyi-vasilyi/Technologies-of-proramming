#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include <memory>
#include "shape.hpp"

namespace pochetnyi
{
  class CompositeShape : public Shape
  {
  public:
    CompositeShape();
    CompositeShape(const CompositeShape &rhs);
    CompositeShape(CompositeShape &&rhs);
    ~CompositeShape() = default;

    CompositeShape &operator=(const CompositeShape &rhs);
    CompositeShape &operator=(CompositeShape &&rhs);
    SharedShapePtr operator[](size_t index) const;

    size_t getCount() const;
    void addShape(SharedShapePtr &rhs);
    void removeShape(size_t index);
    void clearList();

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void scale(double coef) override;
    void rotate(double degrees) override;
    void move(const point_t &point) override;
    void move(double dx, double dy) override;
    point_t getCenter() const override;
    void printInfo() const override;

  private:
    std::unique_ptr<SharedShapePtr[]> list_;
    size_t count_;
  };
}

#endif // COMPOSITE_SHAPE_HPP
