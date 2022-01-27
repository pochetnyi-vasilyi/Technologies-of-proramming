#include "commands.hpp"
#include <string>
#include <iostream>
#include <sstream>
#include "user-interface.hpp"

std::istringstream &pochetnyi::operator>>(std::istringstream &in, NameRef name)
{
  std::ios_base::fmtflags flags = in.flags();
  in >> std::ws;
  if (in.get() != '"')
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  in >> std::noskipws;

  std::string newName;
  std::string temp;

  while ((std::getline(in, temp, '"') && (!in.eof())))
  {
    newName += temp;
    if (newName.back() == '\\')
    {
      newName.back() = '"';
    }
    temp = "";
  }
  if (in.eof())
  {
    if (!temp.empty())
    {
      for (char &c : temp)
      {
        if (!std::isspace(c))
        {
          in.setstate(std::ios::failbit);
          return in;
        }
      }
    }
    in.clear();
  }
  name.name_ = newName;
  in.setf(flags);
  return in;
}

std::istringstream &pochetnyi::operator>>(std::istringstream &in, PhoneRef phone)
{
  std::string number;
  in >> number;
  if (number.empty())
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  for (char &c : number)
  {
    if (!isdigit(c))
    {
      in.setstate(std::ios::failbit);
      return in;
    }
  }
  phone.phone_ = number;
  return in;
}

std::istringstream &pochetnyi::operator>>(std::istringstream &in, BookmarkRef mark)
{
  std::string bookmark;
  in >> bookmark;
  if (bookmark.empty())
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  for (char &c : bookmark)
  {
    if (!std::isalnum(c) && (c != '-'))
    {
      in.setstate(std::ios::failbit);
      return in;
    }
  }
  mark.mark_ = bookmark;
  return in;
}

void pochetnyi::readCommand(const std::string &inputStr, Interface &ui)
{
  std::istringstream in(inputStr);
  std::string command;
  in >> command >> std::ws;

  std::map<std::string, void (*)(std::istringstream &, Interface &)>::const_iterator it = commandsMap.find(command);
  if (it == commandsMap.end())
  {
    throw std::invalid_argument(INVALID_COMMAND);
  }
  it->second(in, ui);
}

void pochetnyi::add(std::istringstream &in, Interface &ui)
{
  std::string phone;
  std::string name;
  if (!(in >> PhoneRef{ phone } >> NameRef{ name }))
  {
    throw std::invalid_argument(INVALID_COMMAND);
  }
  ui.addRecord(name, phone);
}

void pochetnyi::store(std::istringstream &in, Interface &ui)
{
  std::string currentMark;
  std::string newMark;
  if (!(in >> BookmarkRef{ currentMark } >> BookmarkRef{ newMark }))
  {
    throw std::invalid_argument(INVALID_COMMAND);
  }
  ui.store(currentMark, newMark);
}

void pochetnyi::insert(std::istringstream &in, Interface &ui)
{
  std::string position;
  in >> position;
  std::string bookmark;
  std::string phone;
  std::string name;
  if (!(in >> BookmarkRef{ bookmark } >> PhoneRef{ phone } >> NameRef{ name }))
  {
    throw std::invalid_argument(INVALID_COMMAND);
  }

  if ((position == "before") || (position == "after"))
  {
    ui.insert(bookmark, name, phone, position);
  }
  else
  {
    throw std::invalid_argument(INVALID_COMMAND);
  }
}

void pochetnyi::deleteMark(std::istringstream &in, Interface &ui)
{
  std::string bm;
  if (!(in >> BookmarkRef{ bm }))
  {
    throw std::invalid_argument(INVALID_COMMAND);
  }
  ui.deleteBookMark(bm);
}

void pochetnyi::show(std::istringstream &in, Interface &ui)
{
  std::string bm;
  if (!(in >> BookmarkRef{ bm }))
  {
    throw std::invalid_argument(INVALID_COMMAND);
  }
  ui.show(bm);
}

void pochetnyi::move(std::istringstream &in, Interface &ui)
{
  std::string bm;
  if (!(in >> BookmarkRef{ bm }))
  {
    throw std::invalid_argument(INVALID_COMMAND);
  }
  std::string step;
  in >> step;
  if (step.empty())
  {
    throw std::invalid_argument(INVALID_COMMAND);
  }
  if ((step == "first") || (step == "last"))
  {
    ui.move(bm, step);
  }
  else
  {
    int steps = 0;
    try
    {
      size_t pos = 0;
      steps = std::stoi(step, &pos);
      if (pos != step.length())
      {
        throw std::invalid_argument(INVALID_STEP);
      }
    }
    catch (const std::exception &error)
    {
      std::cout << INVALID_STEP;
      return;
    }
    ui.move(bm, steps);
  }
}
