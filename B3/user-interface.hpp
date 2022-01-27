#ifndef INTERFACE
#define INTERFACE

#include "phone-book.hpp"
#include <cstring>
#include <list>

namespace pochetnyi
{
  const std::string EMPTY = "<EMPTY>\n";
  const std::string INVALID_STEP = "<INVALID STEP>\n";
  const std::string INVALID_COMMAND = "<INVALID COMMAND>\n";
  const std::string INVALID_BOOKMARK = "<INVALID BOOKMARK>\n";

  class Interface
  {
  public:
    struct bookmark_t
    {
      std::string name;
      std::list<pochetnyi::PhoneBook::record_t>::iterator record;
    };
    typedef std::list<bookmark_t>::iterator bmIter;

    Interface();
    void addRecord(const std::string &name, const std::string &phone);
    void store(const std::string &currentMark, const std::string &newMark);
    void insert(const std::string &bookmark, const std::string &name, const std::string &phone, const std::string &place);
    void deleteBookMark(const std::string &bookmark);
    void show(const std::string &bookmark);
    void move(const std::string &bookmark, const int steps);
    void move(const std::string &bookmark, const std::string &place);

  private:
    bmIter findBookmark(const std::string &bookmark);

    PhoneBook phoneBook_;
    std::list<bookmark_t> bookmarks_;
  };
}

#endif
