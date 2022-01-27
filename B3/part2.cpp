#include "parts.hpp"
#include <iostream>
#include <algorithm>
#include "factorial-container.hpp"

void pochetnyi::part2()
{
  FactorialContainer container;

  std::copy(container.begin(), container.end(), std::ostream_iterator<unsigned int>(std::cout, " "));
  std::cout << '\n';
  std::reverse_copy(container.begin(), container.end(), std::ostream_iterator<unsigned int>(std::cout, " "));
  std::cout << '\n';
}
