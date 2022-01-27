#include "parts.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include "queue-with-priority.hpp"

void print(const std::string &string);

void pochetnyi::part1()
{
  QueueWithPriority<std::string> queue;
  std::string input;

  while (std::getline(std::cin, input))
  {
    std::istringstream inputStr(input);
    std::string command;
    inputStr >> command >> std::ws;

    if ((command == "add") && (!inputStr.eof()))
    {
      std::string priority;
      inputStr >> priority >> std::ws;
      std::string data;
      std::getline(inputStr, data);

      if (data.empty() || priority.empty())
      {
        std::cout << "<INVALID COMMAND>\n";
      }
      if (priority == "high")
      {
        queue.putElement(data, pochetnyi::QueueWithPriority<std::string>::ElementPriority::HIGH);
      }
      else if (priority == "low")
      {
        queue.putElement(data, pochetnyi::QueueWithPriority<std::string>::ElementPriority::LOW);
      }
      else if (priority == "normal")
      {
        queue.putElement(data, pochetnyi::QueueWithPriority<std::string>::ElementPriority::NORMAL);
      }
      else
      {
        std::cout << "<INVALID COMMAND>\n";
      }
    }
    else if ((command == "get") && (inputStr.eof()))
    {
      if (queue.isEmpty())
      {
        std::cout << "<EMPTY>\n";
      }
      else
      {
        queue.popElement(print);
      }
    }
    else if ((command == "accelerate") && (inputStr.eof()))
    {
      queue.accelerate();
    }
    else
    {
      std::cout << ("<INVALID COMMAND>\n");
    }
  }
  if (!std::cin.eof())
  {
    throw std::runtime_error("Command reading error!");
  }
}

void print(const std::string &string)
{
  std::cout << string << '\n';
}
