#include "base-types.hpp"
#include <cmath>

bool pochetnyi::detail::checkOverlaying(const rectangle_t &frameRect1, const rectangle_t &frameRect2)
{
  const double diffX = std::abs(frameRect2.pos.x - frameRect1.pos.x);
  const double diffY = std::abs(frameRect2.pos.y - frameRect1.pos.y);
  const double halfWidth = frameRect1.width / 2.0 + frameRect2.width / 2.0;
  const double halfHeight = frameRect1.height / 2.0 + frameRect2.height / 2.0;
  if ((diffX <= halfWidth) && (diffY <= halfHeight))
  {
    return true;
  }
  return false;
}
