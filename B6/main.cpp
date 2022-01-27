#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include "functor.hpp"

int main()
{
  pochetnyi::Functor functor = std::for_each(std::istream_iterator<int>(std::cin), std::istream_iterator<int>(), pochetnyi::Functor());
  if (!std::cin.eof() && std::cin.fail())
  {
    std::cerr << "Invalid input!\n";
    return 1;
  }
  std::cout << functor;

  return 0;
}
