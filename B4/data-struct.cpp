#include "data-struct.hpp"
#include <iostream>
#include <sstream>
#include "../common/stream-guard.hpp"
#include "../common/skip-blank.hpp"

bool pochetnyi::operator<(const DataStruct &lhs, const DataStruct &rhs)
{
  if (lhs.key1 == rhs.key1)
  {
    if (lhs.key2 == rhs.key2)
    {
      return lhs.str.length() < rhs.str.length();
    }
    return lhs.key2 < rhs.key2;
  }
  return lhs.key1 < rhs.key1;
}

std::istream &pochetnyi::operator>>(std::istream &in, DataStruct &dataStruct)
{
  StreamGuard guard(in);
  in >> std::noskipws;

  int key1;
  in >> detail::skipBlank >> key1;
  if (!in || !isKeyInRange(key1))
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  char delim;
  in >> detail::skipBlank >> delim;
  if ((delim != DELIMITER) || !in)
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  int key2;
  in >> detail::skipBlank >> key2;
  if (!in || !isKeyInRange(key2))
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  in >> detail::skipBlank >> delim;
  if ((delim != DELIMITER) || !in)
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  std::string str;
  getline(in >> detail::skipBlank, str);

  if (!in)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  dataStruct.key1 = key1;
  dataStruct.key2 = key2;
  dataStruct.str = str;

  return in;
}

std::ostream &pochetnyi::operator<<(std::ostream &out, const DataStruct &dataStruct)
{
  out << dataStruct.key1 << DELIMITER << dataStruct.key2 << DELIMITER << dataStruct.str;
  return out;
}

bool pochetnyi::isKeyInRange(const int key)
{
  return (key >= MIN_VAL) && (key <= MAX_VAL);
}
