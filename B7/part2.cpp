#include "parts.hpp"
#include <string>
#include <iterator>
#include <algorithm>
#include <stdexcept>
#include <map>
#include "skip-blank.hpp"
#include "stream-guard.hpp"

template <class T>
std::shared_ptr<pochetnyi::Shape> createShape(pochetnyi::Point &point)
{
  return std::shared_ptr<pochetnyi::Shape>{ new T(point) };
}

const std::map<std::string, pochetnyi::addShape> shapeMap({
  { "CIRCLE", &createShape<pochetnyi::Circle> },
  { "TRIANGLE", &createShape<pochetnyi::Triangle> },
  { "SQUARE", &createShape<pochetnyi::Square> }
});

std::istream &pochetnyi::operator>>(std::istream &in, std::vector<std::shared_ptr<Shape>> &shapesVector)
{
  StreamGuard guard(in);
  in >> std::noskipws;
  while (!(in >> std::ws).eof())
  {
    std::string figure;
    char sym;
    in >> detail::skipBlank;
    if (!in.good())
    {
      return in;
    }
    while (std::isalpha(in.peek()))
    {
      in >> sym;
      figure += sym;
    }
    std::map<std::string, pochetnyi::addShape>::const_iterator cIter = shapeMap.find(figure);
    if (cIter == shapeMap.end())
    {
      in.setstate(std::ios::failbit);
      return in;
    }

    Point newPoint{};
    in >> newPoint;

    shapesVector.push_back(cIter->second(newPoint));
  }
  return in;
}

std::ostream &pochetnyi::operator<<(std::ostream &stream, std::shared_ptr<Shape> shape)
{
  stream << *shape;
  return stream;
}

void pochetnyi::part2(std::istream &in, std::ostream &out)
{
  std::vector<std::shared_ptr<Shape>> shapesVector;
  in >> shapesVector;
  if (in.fail())
  {
    throw std::invalid_argument("Invalid input!");
  }

  out << "Original:\n";
  std::copy(shapesVector.begin(), shapesVector.end(), std::ostream_iterator<std::shared_ptr<Shape>>(out, "\n"));

  std::sort(shapesVector.begin(), shapesVector.end(), [](const std::shared_ptr<Shape> &shape1, const std::shared_ptr<Shape> &shape2)
  {
    return shape1->isMoreLeft(*shape2);
  });
  out << "Left-Right:\n";
  std::copy(shapesVector.begin(), shapesVector.end(), std::ostream_iterator<std::shared_ptr<Shape>>(out, "\n"));

  std::sort(shapesVector.begin(), shapesVector.end(), [](const std::shared_ptr<Shape> &shape1, const std::shared_ptr<Shape> &shape2)
  {
    return !(shape1->isMoreLeft(*shape2));
  });
  out << "Right-Left:\n";
  std::copy(shapesVector.begin(), shapesVector.end(), std::ostream_iterator<std::shared_ptr<Shape>>(out, "\n"));

  std::sort(shapesVector.begin(), shapesVector.end(), [](const std::shared_ptr<Shape> &shape1, const std::shared_ptr<Shape> &shape2)
  {
    return shape1->isUpper(*shape2);
  });
  out << "Top-Bottom:\n";
  std::copy(shapesVector.begin(), shapesVector.end(), std::ostream_iterator<std::shared_ptr<Shape>>(out, "\n"));

  std::sort(shapesVector.begin(), shapesVector.end(), [](const std::shared_ptr<Shape> &shape1, const std::shared_ptr<Shape> &shape2)
  {
    return !(shape1->isUpper(*shape2));
  });
  out << "Bottom-Top:\n";
  std::copy(shapesVector.begin(), shapesVector.end(), std::ostream_iterator<std::shared_ptr<Shape>>(out, "\n"));
}
