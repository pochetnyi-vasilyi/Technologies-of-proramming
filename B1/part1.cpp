#include <vector>
#include <forward_list>
#include "detail.hpp"

void part1(pochetnyi::detail::Direction direction)
{
  std::vector<int> vectorByIndex;

  int i = 0;
  while (std::cin >> i)
  {
    vectorByIndex.push_back(i);
  }
  if (!std::cin.eof())
  {
    throw std::ios_base::failure("Data reading failure!");
  }

  if (vectorByIndex.empty())
  {
    return;
  }

  std::vector<int> vectorByAt(vectorByIndex);
  pochetnyi::sort<pochetnyi::IndexAccess>(vectorByIndex, direction);
  std::forward_list<int> listByIterator(vectorByAt.begin(), vectorByAt.end());
  pochetnyi::sort<pochetnyi::AtAccess>(vectorByAt, direction);
  pochetnyi::sort<pochetnyi::IteratorAccess>(listByIterator, direction);

  pochetnyi::print(vectorByIndex);
  pochetnyi::print(vectorByAt);
  pochetnyi::print(listByIterator);
}
