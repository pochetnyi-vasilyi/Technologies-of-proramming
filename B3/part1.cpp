#include "parts.hpp"
#include <iostream>
#include "user-interface.hpp"
#include "commands.hpp"

void pochetnyi::part1()
{
  Interface ui;
  std::string cmd;

  while (std::getline(std::cin, cmd, '\n'))
  {
    try
    {
      readCommand(cmd, ui);
    }
    catch (std::invalid_argument &error)
    {
      std::cout << error.what();
    }
  }
  if (!std::cin.eof())
  {
    throw std::runtime_error("Command reading error!");
  }
}
