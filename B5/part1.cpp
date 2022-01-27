#include "parts.hpp"
#include <iostream>
#include <iterator>
#include <set>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <cctype>

void pochetnyi::part1()
{
  std::set<std::string> words{ std::istream_iterator<std::string>(std::cin), std::istream_iterator<std::string>() };
  if( !std::cin.eof() && std::cin.fail() )
  {
    throw std::runtime_error("Invalid input!");
  }
  std::copy(words.cbegin(), words.cend(), std::ostream_iterator<std::string>(std::cout, "\n"));
}
