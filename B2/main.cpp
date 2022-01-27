#include <iostream>
#include <stdexcept>
#include <cstring>
#include "parts.hpp"

int main(int argc, char *argv[])
{
  try
  {
    if ((argc != 2) || (argv[1] == nullptr))
    {
      throw std::invalid_argument("Invalid number of arguments!");
    }
    int taskNumber = 0;
    size_t numberPos = 0;
    try
    {
      taskNumber = std::stoi(argv[1], &numberPos);
    }
    catch (const std::invalid_argument &error)
    {
      std::cerr << "Invalid task number!";
      return 1;
    }
    catch (const std::out_of_range &error)
    {
      std::cerr << "Task number is out of range!";
      return 1;
    }
    if(numberPos != std::strlen(argv[1]))
    {
      std::cerr << "Task number must consist only numbers!";
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
        throw std::invalid_argument("Invalid task number!");
    }
  }
  catch (std::invalid_argument &error)
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
