#include "point.hpp"
#include <cmath>
#include <sstream>
#include "stream-guard.hpp"
#include "skip-blank.hpp"

double pochetnyi::getLength(const Point &a, const Point &b)
{
  return pow((b.x - a.x), 2) + pow((b.y - a.y), 2);
}

std::ostream &pochetnyi::operator<<(std::ostream &out, const Point &point)
{
  out << "(" << point.x << "; " << point.y << ")";
  return out;
}

std::istream &pochetnyi::operator>>(std::istream &in, Point &point)
{
  StreamGuard guard(in);
  in >> std::noskipws;

  char sym;
  in >> detail::skipBlank >> sym;
  if (!in || (sym != '('))
  {
    in.setstate(std::ios::failbit);
    if (in.eof())
    {
      return in;
    }
    return in.putback(sym);
  }

  int x;
  in >> detail::skipBlank >> x;
  if (!in)
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  in >> detail::skipBlank >> sym;
  if (!in || (sym != ';'))
  {
    in.setstate(std::ios::failbit);
    if (in.eof())
    {
      return in;
    }
    return in.putback(sym);
  }

  int y;
  in >> detail::skipBlank >> y;
  if (!in)
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  in >> detail::skipBlank >> sym;
  if (!in || (sym != ')'))
  {
    in.setstate(std::ios::failbit);
    if (in.eof())
    {
      return in;
    }
    return in.putback(sym);
  }

  point = { x, y };
  return in;
}
