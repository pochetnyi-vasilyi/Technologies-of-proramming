#include <iostream>
#include <stdexcept>
#include <vector>
#include <cstring>
#include <random>
#include "detail.hpp"

void fillRandom(double* array, size_t size)
{
  static std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<double> distribution(-1.0, 1.0);

  for (size_t i = 0; i < size; i++)
  {
    array[i] = distribution(gen);
  }
}

void part4(pochetnyi::detail::Direction direction, const int size)
{
  if (size < 1)
  {
    throw std::invalid_argument("Invalid array size!");
  }
  std::vector<double> vector(size);
  fillRandom(vector.data(), size);
  pochetnyi::print(vector);
  pochetnyi::sort<pochetnyi::IndexAccess>(vector, direction);
  pochetnyi::print(vector);
}
