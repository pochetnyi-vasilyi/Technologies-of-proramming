#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>
#include <vector>

namespace pochetnyi
{
  struct Point
  {
    int x, y;
  };

  double getLength(const Point &a, const Point &b);

  std::istream &operator>>(std::istream &in, Point &point);
  std::ostream &operator<<(std::ostream &out, const Point &point);
}

#endif
