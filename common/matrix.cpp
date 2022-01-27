#include "matrix.hpp"
#include <algorithm>
#include <iostream>
#include <memory>
#include <stdexcept>
#include "shape.hpp"
#include "base-types.hpp"

pochetnyi::Matrix::Layer::Layer(Shape::SharedShapePtr *layer, size_t count):
  layer_(layer),
  count_(count)
{}

pochetnyi::Shape::SharedShapePtr pochetnyi::Matrix::Layer::operator[](size_t index)
{
  if (index >= count_)
  {
    throw std::out_of_range("Index is out of range!");
  }
  return layer_[index];
}

const pochetnyi::Shape::SharedShapePtr pochetnyi::Matrix::Layer::operator[](size_t index) const
{
  if (index >= count_)
  {
    throw std::out_of_range("Index is out of range!");
  }
  return layer_[index];
}

pochetnyi::Matrix::Matrix() :
  layers_(0),
  sizeOfLayer_(0)
{}

pochetnyi::Matrix::Matrix(const Matrix &rhs) :
  layers_(rhs.layers_),
  sizeOfLayer_(rhs.sizeOfLayer_),
  list_(std::make_unique<pochetnyi::Shape::SharedShapePtr[]>(rhs.layers_ * rhs.sizeOfLayer_))
{
  std::copy(rhs.list_.get(), rhs.list_.get() + layers_ * sizeOfLayer_, list_.get());
}

pochetnyi::Matrix::Matrix(Matrix &&rhs) :
  layers_(rhs.layers_),
  sizeOfLayer_(rhs.sizeOfLayer_),
  list_(std::move(rhs.list_))
{
  rhs.layers_ = 0;
  rhs.sizeOfLayer_ = 0;
}

pochetnyi::Matrix::~Matrix()
{
  layers_ = 0;
  sizeOfLayer_ = 0;
}

pochetnyi::Matrix& pochetnyi::Matrix::operator=(const Matrix &rhs)
{
  if (this == &rhs)
  {
    return *this;
  }
  layers_ = rhs.layers_;
  sizeOfLayer_ = rhs.sizeOfLayer_;
  std::unique_ptr<pochetnyi::Shape::SharedShapePtr[]> newMatrix
      = std::make_unique<Shape::SharedShapePtr[]>(layers_ * sizeOfLayer_);
  for (size_t i = 0; i < layers_ * sizeOfLayer_; i++)
  {
    newMatrix[i] = rhs.list_[i];
  }
  list_.swap(newMatrix);
  return *this;
}

pochetnyi::Matrix& pochetnyi::Matrix::operator=(Matrix &&rhs)
{
  if (this == &rhs)
  {
    return *this;
  }
  layers_ = rhs.layers_;
  sizeOfLayer_ = rhs.sizeOfLayer_;
  list_ = std::move(rhs.list_);
  rhs.layers_ = 0;
  rhs.sizeOfLayer_ = 0;
  return *this;
}

pochetnyi::Matrix::Layer pochetnyi::Matrix::operator[](size_t index)
{
  if (index >= layers_)
  {
    throw std::out_of_range("Index is out of range!");
  }
  pochetnyi::Matrix::Layer layer(&list_[index * layers_], sizeOfLayer_);
  return layer;
}

const pochetnyi::Matrix::Layer pochetnyi::Matrix::operator[](size_t index) const
{
  if (index >= layers_)
  {
    throw std::out_of_range("Index is out of range!");
  }
  pochetnyi::Matrix::Layer layer(&list_[index * layers_], sizeOfLayer_);
  return layer;
}

void pochetnyi::Matrix::addShape(const Shape::SharedShapePtr &shape)
{
  if (!shape)
  {
    throw std::invalid_argument("Null shape pointer!");
  }
  std::unique_ptr<pochetnyi::Shape::SharedShapePtr[]> newList = nullptr;
  size_t layerNumber = getLayerNumber(shape);
  size_t position = getPositionNumber(layerNumber);
  if((layerNumber != layers_) && (position != sizeOfLayer_))
  {
    list_[layerNumber * sizeOfLayer_ + position] = shape;
    return;
  }
  if (layerNumber == layers_)
  {
    layers_++;
    newList = std::make_unique<pochetnyi::Shape::SharedShapePtr[]>(layers_ * sizeOfLayer_);
    addLayer(newList);
  }
  if (position == sizeOfLayer_)
  {
    sizeOfLayer_++;
    newList = std::make_unique<pochetnyi::Shape::SharedShapePtr[]>(layers_ * sizeOfLayer_);
    addColumn(newList);
  }
  newList[layerNumber * sizeOfLayer_ + position] = shape;
  list_ = std::move(newList);
}

void pochetnyi::Matrix::addColumn(const std::unique_ptr<pochetnyi::Shape::SharedShapePtr[]> &list)
{
  for (size_t i = 0; i < layers_; i++)
  {
    for (size_t j = 0; j < sizeOfLayer_; j++)
    {
      if (j == (sizeOfLayer_ - 1))
      {
        list[i * sizeOfLayer_ + j] = nullptr;
        continue;
      }
      list[i * sizeOfLayer_ + j] = list_[i * (sizeOfLayer_ - 1) + j];
    }
  }
}

void pochetnyi::Matrix::addLayer(const std::unique_ptr<pochetnyi::Shape::SharedShapePtr[]> &list)
{
  for (size_t i = 0; i < layers_; i++)
  {
    for (size_t j = 0; j < sizeOfLayer_; j++)
    {
      if (i == (layers_ - 1))
      {
        list[i * sizeOfLayer_ + j] = nullptr;
        continue;
      }
      list[i * sizeOfLayer_ + j] = list_[i * sizeOfLayer_ + j];
    }
  }
}

size_t pochetnyi::Matrix::getLayers() const
{
  return layers_;
}

size_t pochetnyi::Matrix::getLayerSize() const
{
  return sizeOfLayer_;
}

size_t pochetnyi::Matrix::getLayerNumber(const Shape::SharedShapePtr &shape)
{
  size_t layerNumber = 0;
  for (size_t i = 0; i < layers_ * sizeOfLayer_; i++)
  {
    if (pochetnyi::detail::checkOverlaying(shape->getFrameRect(), list_[i]->getFrameRect()))
    {
      layerNumber = i / sizeOfLayer_ + 1;
    }
  }
  return layerNumber;
}

size_t pochetnyi::Matrix::getPositionNumber(size_t layerNumber)
{
  if (layerNumber >= layers_)
  {
    return 0;
  }
  size_t position = sizeOfLayer_;
  size_t existShapes = layerNumber * sizeOfLayer_;
  for (size_t i = existShapes; i < existShapes + sizeOfLayer_; i++)
  {
    if (list_[i] == nullptr)
    {
      position = i - existShapes + 1;
      break;
    }
  }
  return position;
}

void pochetnyi::Matrix::printInfo() const
{
  std::cout << "\nMatrix contains " << layers_ << " rows and " << sizeOfLayer_ << " columns. Shapes in matrix:\n";
  for (size_t i = 0; i < layers_; ++i)
  {
    std::cout << "Lay " << i + 1 << ":\n";
    for (size_t j = 0; j < sizeOfLayer_; ++j)
    {
      if (list_[i * sizeOfLayer_ + j] != nullptr)
      {
        std::cout << j + 1 << ". ";
        list_[i * sizeOfLayer_ + j]->printInfo();
      }
    }
  }
}
