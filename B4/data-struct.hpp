#ifndef DATA_STRUCT
#define DATA_STRUCT

#include <iostream>
#include <string>

namespace pochetnyi
{
  struct DataStruct
  {
    int key1;
    int key2;
    std::string str;
  };

  const int MIN_VAL = -5;
  const int MAX_VAL = 5;
  const char DELIMITER = ',';

  bool operator<(const DataStruct &lhs, const DataStruct &rhs);
  std::istream &operator>>(std::istream &in, DataStruct &dataStruct);
  std::ostream &operator<<(std::ostream &out, const DataStruct &dataStruct);

  bool isKeyInRange(const int key);
}

#endif
