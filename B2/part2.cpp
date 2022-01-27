#include "parts.hpp"
#include <iostream>
#include <stdexcept>
#include <list>

void pochetnyi::part2()
{
  std::list<int> list;
  const size_t maxListSize = 20;
  size_t counter = 0;

  int num = 0;
  const int minNum = 1;
  const int maxNum = 20;

  while (std::cin >> num)
  {
    if ((num > maxNum) || (num < minNum))
    {
      throw std::invalid_argument("Invalid input! Only numbers from 1 to 20 allowed.");
    }

    list.push_back(num);
    counter++;

    if (counter > maxListSize)
    {
      throw std::invalid_argument("Invalid input! Only 20 numbers allowed.");
    }
  }

  if (std::cin.fail() && !std::cin.eof())
  {
    throw std::runtime_error("Error reading numbers!");
  }

  std::list<int>::const_iterator beginIter = list.begin();
  std::list<int>::const_iterator endIter = list.end();
  while (beginIter != endIter)
  {
    std::cout << *beginIter++;
    if (beginIter == endIter)
    {
      break;
    }
    std::cout << ' ' << *(--endIter);
    if (beginIter != endIter)
    {
      std::cout << ' ';
    }
  }
  std::cout << '\n';
}
