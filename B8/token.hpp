#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

namespace pochetnyi
{
  struct token_t
  {
    enum State
    {
      WORD,
      NUM,
      DASH,
      ITEM
    };

    State state;
    std::string value;
  };
}

#endif
