#include <stdexcept>
#include "detail.hpp"

pochetnyi::detail::Direction pochetnyi::detail::getDirection(const char* direction)
{
  if (std::strcmp(direction, "ascending") == 0)
  {
    return detail::Direction::ASCENDING;
  }
  else if (std::strcmp(direction, "descending") == 0)
  {
    return detail::Direction::DESCENDING;
  }
  else
  {
    throw std::invalid_argument("Invalid sort direction!");
  }
}
