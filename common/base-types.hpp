#ifndef BASE_TYPES_HPP
#define BASE_TYPES_HPP

namespace pochetnyi
{
  struct point_t
  {
    double x;
    double y;
  };

  struct rectangle_t
  {
    double width;
    double height;
    point_t pos;
  };

  namespace detail
  {
    bool checkOverlaying(const rectangle_t &frameRect1, const rectangle_t &frameRect2);
  }
}

#endif
