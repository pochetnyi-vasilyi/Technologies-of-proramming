#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <memory>
#include "shape.hpp"

namespace pochetnyi
{
  class Matrix
  {
  public:
    class Layer
    {
    public:
      Shape::SharedShapePtr operator[] (size_t index);
      const Shape::SharedShapePtr operator[] (size_t index) const;

    private:
      friend class Matrix;
      Shape::SharedShapePtr *layer_;
      size_t count_;
      Layer(Shape::SharedShapePtr *layer, size_t count);
    };

    Matrix();
    Matrix(const Matrix &rhs);
    Matrix(Matrix &&rhs);
    ~Matrix();

    Matrix& operator=(const Matrix &rhs);
    Matrix& operator=(Matrix &&rhs);
    Layer operator[](size_t index);
    const Layer operator[](size_t index) const;

    size_t getLayers() const;
    size_t getLayerSize() const;
    void addShape(const Shape::SharedShapePtr &shape);
    void printInfo() const;

  private:
    size_t layers_;
    size_t sizeOfLayer_;
    std::unique_ptr<Shape::SharedShapePtr[]> list_;

    size_t getLayerNumber(const Shape::SharedShapePtr &shape);
    size_t getPositionNumber(size_t layerNumber);
    void addLayer(const std::unique_ptr<Shape::SharedShapePtr[]> &list);
    void addColumn(const std::unique_ptr<Shape::SharedShapePtr[]> &list);
  };
}

#endif
