#ifndef COMMANDS
#define COMMANDS

#include <string>
#include <sstream>
#include <map>
#include <cstring>
#include "user-interface.hpp"

namespace pochetnyi
{
  void readCommand(const std::string &inputStr, Interface &ui);
  void add(std::istringstream &in, Interface &ui);
  void store(std::istringstream &in, Interface &ui);
  void insert(std::istringstream &in, Interface &ui);
  void deleteMark(std::istringstream &in, Interface &ui);
  void show(std::istringstream &in, Interface &ui);
  void move(std::istringstream &in, Interface &ui);

  struct NameRef
  {
    std::string &name_;
  };

  struct PhoneRef
  {
    std::string &phone_;
  };

  struct BookmarkRef
  {
    std::string &mark_;
  };

  std::istringstream &operator>>(std::istringstream &in, NameRef name);
  std::istringstream &operator>>(std::istringstream &in, PhoneRef phone);
  std::istringstream &operator>>(std::istringstream &in, BookmarkRef bookmark);

  const std::map<std::string, void (*)(std::istringstream &, Interface &)> commandsMap
  {
    {"add", add},
    {"store", store},
    {"insert", insert},
    {"delete", deleteMark},
    {"show", show},
    {"move", move}
  };
}
#endif
