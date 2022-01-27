#ifndef TEXT_HANDLER_HPP
#define TEXT_HANDLER_HPP

#include <vector>
#include "token.hpp"

namespace pochetnyi
{
  const size_t MAX_SIZE = 20;
  const size_t DEFAULT_STRING_LENGTH = 40;
  const size_t MIN_STRING_LENGTH = 24;

  class TextHandler
  {
  public:
    TextHandler(size_t strLength);

    void preRead(std::istream &in);
    void read(std::istream &in);
    void print(std::ostream &out);

  private:
    token_t token_;
    bool isState_;
    bool isItem_;
    size_t textLength_;
    size_t stringLength_;
    token_t::State curState_;
    std::vector<token_t> text_;

    token_t::State getCurState(char i);
    void countTextLength();
    std::vector<token_t>::iterator getLastTokenIter();
  };
}

#endif
