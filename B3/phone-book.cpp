#include "phone-book.hpp"
#include <stdexcept>

pochetnyi::PhoneBook::PhoneBook() : phones_()
{}

void pochetnyi::PhoneBook::addToEnd(const record_t &record)
{
  phones_.push_back(record);
}

pochetnyi::PhoneBook::recordIter pochetnyi::PhoneBook::insertBefore(recordIter pos, const record_t &record)
{
  return phones_.insert(pos, record);
}

pochetnyi::PhoneBook::recordIter pochetnyi::PhoneBook::insertAfter(recordIter pos, const record_t &record)
{
  if ((phones_.empty()) || (pos != phones_.end()))
  {
    return phones_.insert(std::next(pos), record);
  }
  else
  {
    throw std::out_of_range("Invalid iterator!");
  }
}

pochetnyi::PhoneBook::recordIter pochetnyi::PhoneBook::deleteRecord(recordIter pos)
{
  return phones_.erase(pos);
}

bool pochetnyi::PhoneBook::isEmpty() const
{
  return phones_.empty();
}

pochetnyi::PhoneBook::recordIter pochetnyi::PhoneBook::begin()
{
  return phones_.begin();
}

pochetnyi::PhoneBook::recordIter pochetnyi::PhoneBook::end()
{
  return phones_.end();
}
