#include <iostream>
#include <cstring>
#include <vector>
#include <clocale>
#include "token.hpp"
#include "text-handler.hpp"

int main(int argc, char *argv[])
{
  std::locale curLoc(std::locale(""));
  std::locale::global(curLoc);
  std::cout.imbue(curLoc);
  std::cin.imbue(curLoc);

  try
  {
    if ((argc != 1) && (argc != 3))
    {
      throw std::invalid_argument("Wrong amount of arguments!");
    }

    size_t stringLength = pochetnyi::DEFAULT_STRING_LENGTH;
    if (argc == 3)
    {
      if (std::strcmp(argv[1], "--line-width") != 0)
      {
        throw std::invalid_argument("Invalid first argument");
      }
      else
      {
        stringLength = std::atoi(argv[2]);
        if (stringLength <= pochetnyi::MIN_STRING_LENGTH)
        {
          throw std::invalid_argument("Line width should be more than 0");
        }
      }

      try
      {
        size_t numberPos = 0;
        stringLength = std::stoi(argv[2], &numberPos);
        if (numberPos != std::strlen(argv[2]))
        {
          throw std::invalid_argument("The argument is incorrect");
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
    }

    pochetnyi::TextHandler tH(stringLength);
    tH.preRead(std::cin);

    while (!std::cin.eof())
    {
      tH.read(std::cin);
      tH.print(std::cout);
    }
  }
  catch (std::invalid_argument &error)
  {
    std::cerr << error.what() << '\n';
    return 1;
  }
  catch (...)
  {
    std::cerr << "Unknown exception was thrown.\n";
    return 1;
  }

  return 0;
}
