#include <iostream>
#include <stdexcept>
#include <string>
#include "parts.hpp"
#include "detail.hpp"

int main(int argc, char *argv[])
{
  try
  {
    if ((argc < 2) || (argc > 4))
    {
      std::cerr << "Incorrect count of arguments!";
      return 1;
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
        if (argc != 3)
        {
          throw std::invalid_argument("Incorrect count of arguments!");
          return 1;
        }
        pochetnyi::detail::Direction direction;
        direction = pochetnyi::detail::getDirection(argv[2]);
        part1(direction);
        break;
      case 2:
        if (argc != 3)
        {
          throw std::invalid_argument("Incorrect count of arguments!");
          return 1;
        }
        part2(argv[2]);
        break;
      case 3:
        if (argc != 2)
        {
          throw std::invalid_argument("Incorrect count of arguments!");
          return 1;
        }
        part3();
        break;
      case 4:
      {
        if (argc != 4)
        {
          throw std::invalid_argument("Incorrect count of arguments!");
          return 1;
        }
        int size = 0;
        size_t numberPos = 0;
        try
        {
          size = std::stoi(argv[3], &numberPos);
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
        if(numberPos != std::strlen(argv[3]))
        {
          std::cerr << "Task number must consist only numbers!";
          return 1;
        }
        direction = pochetnyi::detail::getDirection(argv[2]);
        part4(direction, size);
        break;
      }
      default:
        std::cerr << "Incorrect task number!";
        return 1;
    }
  }
  catch (const std::exception &error)
  {
    std::cerr << error.what();
    return 1;
  }
  catch (...)
  {
    std::cerr << "Unknown error!";
    return 1;
  }
  return 0;
}
