#include "skip-blank.hpp"
#include <istream>

std::istream &detail::skipBlank(std::istream &in)
{
  while (isblank(in.peek()))
  {
    in.get();
  }
  return in;
}
