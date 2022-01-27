#include "text-handler.hpp"

#include <iostream>
#include <stdexcept>
#include <vector>
#include <cctype>
#include <cstring>

pochetnyi::TextHandler::TextHandler(size_t strLength):
  token_(token_t{ token_t::WORD, "" }),
  isState_(false),
  isItem_(false),
  textLength_(0),
  stringLength_(strLength),
  curState_(token_t::WORD),
  text_(std::vector<token_t>())
{}

pochetnyi::token_t::State pochetnyi::TextHandler::getCurState(char i)
{
  if (isState_)
  {
    text_.push_back(token_);
    countTextLength();
  }

  if (isspace(i))
  {
    isState_ = false;
    return token_.state;
  }
  else if (isalpha(i))
  {
    token_.state = token_t::WORD;
  }
  else if (isdigit(i) || ((i == '-' || i == '+') && isdigit(std::cin.peek())))
  {
    token_.state = token_t::NUM;
  }
  else if (i == '-')
  {
    if (token_.state == token_t::WORD || token_.state == token_t::NUM || (token_.value == ","))
    {
      token_.state = token_t::DASH;
    }
    else
    {
      throw std::invalid_argument("Invalid symbol");
    }
  }
  else if (isItem_)
  {
    if ((token_.state == token_t::WORD) || (token_.state == token_t::NUM))
    {
      token_.state = token_t::ITEM;
    }
    else
    {
      throw std::invalid_argument("Invalid symbol");
    }
  }
  else
  {
    throw std::invalid_argument("Invalid symbol");
  }

  isState_ = true;
  token_.value.clear();
  token_.value.push_back(i);

  return token_.state;
}

void pochetnyi::TextHandler::preRead(std::istream &in)
{
  char i;

  while (isspace(in.peek()))
  {
    i = in.get();
  }

  i = in.get();
  if (in.eof())
  {
    return;
  }
  if (std::strchr(".,:;!?", i) != nullptr)
  {
    isItem_ = true;
  }
  curState_ = getCurState(i);

  if ((token_.state == token_t::DASH) || (token_.state == token_t::ITEM))
  {
    throw std::invalid_argument("Invalid symbol");
  }
}

void pochetnyi::TextHandler::read(std::istream &in)
{
  char i;
  char decimalSeparator = std::use_facet<std::numpunct<char>>(std::cout.getloc()).decimal_point();
  bool hasDecSep = false;

  while (!std::cin.eof() && (textLength_ <= stringLength_))
  {
    i = in.get();
    if (in.eof())
    {
      break;
    }

    if (std::strchr(".,:;!?", i) != nullptr)
    {
      isItem_ = true;
    }

    if (isState_)
    {
      switch (curState_)
      {
        case token_t::WORD:
          if (isalpha(i) || (i == '-'))
          {
            if ((i == '-') && (token_.value.back() == '-'))
            {
              curState_ = getCurState(i);
            }
            else
            {
              if (token_.value.size() < MAX_SIZE)
              {
                token_.value.push_back(i);
              }
              else
              {
                throw std::invalid_argument("Word must contain 20 letters max!");
              }
            }
          }
          else if (isspace(i) || isdigit(i) || isItem_)
          {
            curState_ = getCurState(i);
          }
          else
          {
            throw std::invalid_argument("Invalid symbol!");
          }
          break;

        case token_t::NUM:
          if (isdigit(i))
          {
            if (token_.value.size() < MAX_SIZE)
            {
              token_.value.push_back(i);
            }
            else
            {
              throw std::invalid_argument("Number must contain 20 symbols max!");
            }
          }
          else if (i == decimalSeparator)
          {
            if (hasDecSep)
            {
              curState_ = getCurState(i);
              hasDecSep = false;
            }
            else
            {
              if (token_.value.size() < MAX_SIZE)
              {
                token_.value.push_back(i);
              }
              else
              {
                throw std::invalid_argument("Number must contain 20 symbols max!");
              }
              hasDecSep = true;
            }
          }
          else if (isspace(i) || (i == '-') || isItem_ || isalpha(i))
          {
            curState_ = getCurState(i);
            hasDecSep = false;
          }
          else
          {
            throw std::invalid_argument("Invalid symbol!");
          }
          break;

        case token_t::DASH:
          if ((i == '-') && (token_.value.size() < 3))
          {
            token_.value.push_back(i);
          }
          else if (isspace(i) || isdigit(i) || isalpha(i) || ((i == '-') && isdigit(in.peek())))
          {
            if (token_.value == "---")
            {
              curState_ = getCurState(i);
            }
            else
            {
              throw std::invalid_argument("Invalid symbol!");
            }
          }
          else
          {
            throw std::invalid_argument("Invalid symbol!");
          }
          break;

        case token_t::ITEM:
          if (isspace(i) || isalpha(i) || isdigit(i) || (i == '-'))
          {
            curState_ = getCurState(i);
          }
          else
          {
            throw std::invalid_argument("Invalid symbol!");
          }
          break;
      }
    }
    else
    {
      if (!isspace(i))
      {
        curState_ = getCurState(i);
      }
    }
  }
  if (isState_ && in.eof())
  {
    text_.push_back(token_);
    countTextLength();
  }
}

void pochetnyi::TextHandler::countTextLength()
{
  size_t length = 0;
  size_t vecSize = text_.size();

  if (vecSize == 0)
  {
    textLength_ = length;
    return;
  }

  for (size_t i = 0; i < (vecSize - 1); i++)
  {
    length += text_[i].value.size();
    if (((text_[i].state == token_t::WORD) || (text_[i].state == token_t::NUM)) && (text_[i + 1].state != token_t::ITEM))
    {
      length++;
    }
    else if ((text_[i].state == token_t::ITEM) || (text_[i].state == token_t::DASH))
    {
      length++;
    }
  }
  length += text_[vecSize - 1].value.size();

  textLength_ = length;
}

std::vector<pochetnyi::token_t>::iterator pochetnyi::TextHandler::getLastTokenIter()
{
  std::vector<token_t>::iterator firstElem = text_.begin();
  std::vector<token_t>::iterator penultElem = std::prev(text_.end());
  if (penultElem == firstElem)
  {
    return penultElem;
  }
  std::vector<token_t>::iterator curElem = penultElem;
  size_t curLength = textLength_;

  if (textLength_ > stringLength_)
  {
    while (((curLength > stringLength_) || ((curElem + 1)->state == token_t::ITEM)
        || ((curElem + 1)->state == token_t::DASH)) && (curElem != firstElem))
    {
      curLength = curLength - curElem->value.size();
      curElem--;
      if (((curElem->state == token_t::WORD) || (curElem->state == token_t::NUM)) && ((curElem + 1)->state != token_t::ITEM))
      {
        curLength--;
      }
      else if ((curElem->state == token_t::ITEM) || (curElem->state == token_t::DASH))
      {
        curLength--;
      }
    }

    if ((curElem == firstElem) && (((curElem + 1)->state == token_t::ITEM)
        || ((curElem + 1)->state == token_t::DASH) || (curLength > stringLength_)))
    {
      throw std::invalid_argument("Invalid string length!");
    }
  }

  return curElem;
}

void pochetnyi::TextHandler::print(std::ostream &out)
{
  std::vector<token_t>::iterator begin = text_.begin();
  std::vector<token_t>::iterator end = getLastTokenIter();
  std::vector<token_t>::iterator current = begin;

  while (current != end)
  {
    if (((current->state == token_t::WORD) || (current->state == token_t::NUM)) && ((current + 1)->state != token_t::ITEM))
    {
      out << current->value << " ";
    }
    else if ((current->state == token_t::ITEM) || (current->state == token_t::DASH))
    {
      out << current->value << " ";
    }
    else
    {
      out << current->value;
    }
    current++;
  }
  out << current->value << '\n';

  text_.erase(begin, (end + 1));
  countTextLength();

  if (std::cin.eof() && !(text_.empty()))
  {
    print(out);
  }
}
