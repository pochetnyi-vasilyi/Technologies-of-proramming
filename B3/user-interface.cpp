#include "user-interface.hpp"
#include <iostream>
#include <stdexcept>
#include <string>
#include "phone-book.hpp"

pochetnyi::Interface::Interface() :
  phoneBook_(),
  bookmarks_()
{
  bookmarks_.push_back({ "current", phoneBook_.begin() });
}

pochetnyi::Interface::bmIter pochetnyi::Interface::findBookmark(const std::string &bookmark)
{
  bmIter it;
  for (it = bookmarks_.begin(); it != bookmarks_.end(); it++)
  {
    if (it->name == bookmark)
    {
      return it;
    }
  }
  return it;
}

void pochetnyi::Interface::addRecord(const std::string &name, const std::string &phone)
{
  phoneBook_.addToEnd({ name, phone });
  if (phoneBook_.begin() == std::prev(phoneBook_.end()))
  {
    bookmarks_.begin()->record--;
  }
}

void pochetnyi::Interface::store(const std::string &currentMark, const std::string &newMark)
{
  bmIter it = findBookmark(currentMark);
  if (it == bookmarks_.end())
  {
    throw std::invalid_argument(INVALID_BOOKMARK);
  }
  bookmarks_.push_back({ newMark, it->record });
}

void pochetnyi::Interface::insert(const std::string &bookmark, const std::string &name, const std::string &phone, const std::string &place)
{
  if (phoneBook_.isEmpty())
  {
    phoneBook_.addToEnd({ name, phone });
    bookmarks_.begin()->record = phoneBook_.begin();
  }
  bmIter pos = findBookmark(bookmark);
  if (pos == bookmarks_.end())
  {
    throw std::invalid_argument(INVALID_BOOKMARK);
  }
  PhoneBook::recordIter it;
  if (place == "before")
  {
    it = phoneBook_.insertBefore(pos->record, { name, phone });
  }
  else if (place == "after")
  {
    it = phoneBook_.insertAfter(pos->record, { name, phone });
  }
  else
  {
    throw std::invalid_argument(INVALID_COMMAND);
  }
}

void pochetnyi::Interface::deleteBookMark(const std::string &bookmark)
{
  bmIter bm = findBookmark(bookmark);
  if (bm == bookmarks_.end())
  {
    throw std::invalid_argument(INVALID_BOOKMARK);
  }

  PhoneBook::recordIter contact = bm->record;
  for (bmIter it = bookmarks_.begin(); it != bookmarks_.end(); it++)
  {
    if (it->record == contact)
    {
      if (contact == std::prev(phoneBook_.end()))
      {
        it->record--;
      }
      else
      {
        it->record++;
      }
    }
  }
  phoneBook_.deleteRecord(contact);
}

void pochetnyi::Interface::show(const std::string &bookmark)
{
  bmIter it = findBookmark(bookmark);
  if (it == bookmarks_.end())
  {
    throw std::invalid_argument(INVALID_BOOKMARK);
  }
  if (phoneBook_.isEmpty())
  {
    throw std::invalid_argument(EMPTY);
  }
  std::cout << it->record->phone << ' ' << it->record->name << '\n';
}

void pochetnyi::Interface::move(const std::string &bookmark, const int steps)
{
  bmIter pos = findBookmark(bookmark);
  if (pos == bookmarks_.end())
  {
    throw std::invalid_argument(INVALID_BOOKMARK);
  }

  for (int i = 0; i < std::abs(steps); i++)
  {
    if (steps > 0)
    {
      if (pos->record == std::prev(phoneBook_.end()))
      {
        pos->record = phoneBook_.begin();
      }
      else
      {
        ++pos->record;
      }
    }
    else if (steps < 0)
    {
      if (pos->record == phoneBook_.begin())
      {
        pos->record = std::prev(phoneBook_.end());
      }
      else
      {
        --pos->record;
      }
    }
  }
}

void pochetnyi::Interface::move(const std::string &bookmark, const std::string &place)
{
  bmIter pos = findBookmark(bookmark);
  if (pos == bookmarks_.end())
  {
    throw std::invalid_argument(INVALID_BOOKMARK);
  }
  if (place == "first")
  {
    pos->record = phoneBook_.begin();
  }
  else if (place == "last")
  {
    pos->record = std::prev(phoneBook_.end());
  }
  else
  {
    throw std::invalid_argument(INVALID_STEP);
  }
}
