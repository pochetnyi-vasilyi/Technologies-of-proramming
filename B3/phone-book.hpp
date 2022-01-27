#ifndef PHONE_BOOK
#define PHONE_BOOK

#include <list>
#include <map>
#include <memory>
#include <string>

namespace pochetnyi
{
  class PhoneBook
  {
  public:
  struct record_t
  {
    std::string name;
    std::string phone;
  };
  typedef std::list<record_t>::iterator recordIter;

  PhoneBook();
  void addToEnd(const record_t &record);
  recordIter insertBefore(recordIter pos, const record_t &record);
  recordIter insertAfter(recordIter pos, const record_t &record);
  recordIter deleteRecord(recordIter pos);
  bool isEmpty() const;
  recordIter begin();
  recordIter end();

  private:
    std::list<record_t> phones_;
  };
}
#endif
