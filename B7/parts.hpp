#include <vector>
#include <memory>
#include "circle.hpp"
#include "triangle.hpp"
#include "square.hpp"

namespace pochetnyi
{
  using addShape = std::shared_ptr<Shape>(*)(Point &point);
  std::istream &operator>>(std::istream &in, std::vector<std::shared_ptr<Shape>> &shapes);
  std::ostream &operator<<(std::ostream &stream, std::shared_ptr<Shape> shape);

  void part1(std::istream &in, std::ostream &out);
  void part2(std::istream &in, std::ostream &out);
}
