#include <iostream>
#include <stdexcept>
#include <string>
#include <cstring>
#include "parts.hpp"

int main(int argc, char* argv[])
{
  try
  {
    if ((argc != 2) || (argv[1] == nullptr))
    {
      std::cerr << "Invalid number of arguments!\n";
      return 1;
    }

    int taskNumber = 0;
    size_t numberPos = 0;
    try
    {
      taskNumber = std::stoi(argv[1], &numberPos);
      if (numberPos != std::strlen(argv[1]))
      {
        throw std::invalid_argument("Task number must consist only numbers!");
      }
    }
    catch (std::invalid_argument &error)
    {
      std::cerr << error.what() << '\n';
      return 1;
    }
    catch (std::out_of_range &error)
    {
      std::cerr << "Task number is too big!\n";
      return 1;
    }

    switch (taskNumber)
    {
      case 1:
        pochetnyi::part1();
        break;
      case 2:
        pochetnyi::part2();
        break;
      default:
        std::cerr << "Incorrect task number!\n";
        return 1;
    }
  }
  catch (std::exception &error)
  {
    std::cerr << error.what() << '\n';
    return 1;
  }
  catch (...)
  {
    std::cerr << "Unknown error!\n";
    return 1;
  }

  return 0;
}
