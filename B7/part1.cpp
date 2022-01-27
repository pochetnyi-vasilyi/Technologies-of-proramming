#include "parts.hpp"
#include <math.h>
#include <functional>
#include <algorithm>
#include <iterator>
#include <vector>
#include <iostream>

void pochetnyi::part1(std::istream &in, std::ostream &out)
{
  if (in && out)
  {
    std::transform ((std::istream_iterator<double> (in)), std::istream_iterator<double> (),
        std::ostream_iterator<double> (out, "\n"), std::bind1st(std::multiplies<double>(), M_PI));

    if (!in.eof ())
    {
      throw std::invalid_argument ("Invalid input!");
    }
  }
}
