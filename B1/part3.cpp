#include <iostream>
#include <vector>
#include "detail.hpp"

void part3()
{
  std::vector<int> vector;

  int i = 0;
  while ((std::cin >> i) && (i != 0))
  {
    if (std::cin.fail() || std::cin.bad())
    {
      throw std::ios_base::failure("Data reading failure!");
    }
    vector.push_back(i);
  }
  if (std::cin.fail() && ((i != 0) || !std::cin.eof()))
  {
    vector.clear();
    throw std::ios_base::failure("Invalid input!");
  }

  if (vector.empty())
  {
    return;
  }

  std::vector<int>::iterator iter = vector.begin();

  if (vector.back() == 1)
  {
    while (iter != vector.end())
    {
      if (*iter % 2 == 0)
      {
        iter = vector.erase(iter);
      }
      else
      {
        iter++;
      }
    }
  }
  else if (vector.back() == 2)
  {
    while (iter != vector.end())
    {
      if (*iter % 3 == 0)
      {
        iter = vector.insert(++iter, 3, 1);
        std::advance(iter, 2);
      }
      iter++;
    }
  }
  pochetnyi::print(vector);
}
