#include <stdexcept>
#include <iostream>
#include <iosfwd>
#include <vector>
#include <iterator>
#include <algorithm>
#include "data-struct.hpp"

int main()
{
  try
  {
    using input = std::istream_iterator<pochetnyi::DataStruct>;
    using output = std::ostream_iterator<pochetnyi::DataStruct>;

    std::vector<pochetnyi::DataStruct> vector((input(std::cin)), input());
    if (!std::cin.eof() && std::cin.fail())
    {
      throw std::invalid_argument("Invalid input!");
    }
    std::sort(vector.begin(), vector.end());
    std::copy(vector.begin(), vector.end(), output(std::cout, "\n"));
  }
  catch (const std::invalid_argument &error)
  {
    std::cerr << error.what() << '\n';
    return 1;
  }
  return 0;
}
