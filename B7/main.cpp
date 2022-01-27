#include <iostream>
#include <stdexcept>
#include <string>
#include <cstring>
#include <clocale>
#include "parts.hpp"

int main(int argc, char *argv[])
{
  std::locale commaLoc(std::locale(""));
  std::locale::global(commaLoc);
  std::cout.imbue(commaLoc);
  std::cin.imbue(commaLoc);

  try
  {
    if (argc != 2)
    {
      throw std::invalid_argument("Wrong amount of arguments!");
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
        pochetnyi::part1(std::cin, std::cout);
        break;

      case 2:
        pochetnyi::part2(std::cin, std::cout);
        break;

      default:
        throw std::invalid_argument("Incorrect task number!\n");
    }
  }
  catch (std::ios_base::failure &error)
  {
    std::cerr << error.what() << '\n';
    return 1;
  }
  catch (std::invalid_argument &error)
  {
    std::cerr << error.what() << '\n';
    return 1;
  }
  catch (...)
  {
    std::cerr << "Unknown exception was thrown\n";
    return 1;
  }

  return 0;
}
