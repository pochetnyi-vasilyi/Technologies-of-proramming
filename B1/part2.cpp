#include <fstream>
#include <memory>
#include <vector>
#include <stdexcept>
#include "detail.hpp"

void part2(const char* file)
{
  if (!file)
  {
    throw std::invalid_argument("File name is nullptr!");
  }
  std::ifstream source(file);
  if (!source)
  {
    throw std::runtime_error("Cannot open the file!");
  }

  size_t size = 10;
  size_t count = 0;
  std::unique_ptr<char[]> array(new char[size]);

  while (!source.eof())
  {
    source.read(&array[count], size - count);
    count += source.gcount();
    if(size == count)
    {
      size *= 2;
      std::unique_ptr<char[]> tempArray(new char[size]);
      for (size_t i = 0; i < count; ++i)
      {
        tempArray[i] = array[i];
      }
      array.swap(tempArray);
    }
  }
  if (count == 0)
  {
    return;
  }

  std::vector<char> vector(&array[0], &array[count]);
  std::cout.write(vector.data(),vector.size());
}
