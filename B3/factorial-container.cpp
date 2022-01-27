#include "factorial-container.hpp"
#include <stdexcept>

pochetnyi::FactorialIterator::FactorialIterator() :
  pos_(START),
  value_(START)
{}

pochetnyi::FactorialIterator::FactorialIterator(size_t pos, unsigned int value) :
 pos_(pos),
 value_(value)
{}

pochetnyi::FactorialIterator::FactorialIterator(size_t index)
{
  if ((index < START) || (index > END))
  {
    throw std::out_of_range("Invalid factorial index!");
  }
  pos_ = index;
  value_ = detail::getFactorial(index);
}

pochetnyi::FactorialIterator &pochetnyi::FactorialIterator::operator++()
{
  pos_++;
  if (pos_ > END)
  {
    throw std::out_of_range("Invalid factorial index!\n");
  }
  value_ *= pos_;
  return *this;
}

pochetnyi::FactorialIterator &pochetnyi::FactorialIterator::operator--()
{
  if (pos_ <= START)
  {
    throw std::out_of_range("Invalid factorial index!\n");
  }
  value_ /= pos_--;
  return *this;
}

pochetnyi::FactorialIterator pochetnyi::FactorialIterator::operator++(int)
{
  FactorialIterator temp = *this;
  (*this)++;
  return temp;
}

pochetnyi::FactorialIterator pochetnyi::FactorialIterator::operator--(int)
{
  FactorialIterator temp = *this;
  (*this)--;
  return temp;
}

bool pochetnyi::FactorialIterator::operator==(const FactorialIterator &rhs) const
{
  return pos_ == rhs.pos_;
}

bool pochetnyi::FactorialIterator::operator!=(const FactorialIterator &rhs) const
{
  return pos_ != rhs.pos_;
}

const unsigned int &pochetnyi::FactorialIterator::operator*() const
{
  return value_;
}

const unsigned int* pochetnyi::FactorialIterator::operator->() const
{
  return &value_;
}

pochetnyi::FactorialIterator pochetnyi::FactorialContainer::begin() const
{
  return FactorialIterator(START);
}

pochetnyi::FactorialIterator pochetnyi::FactorialContainer::end() const
{
  return FactorialIterator(END, pochetnyi::FactorialIterator::END_VALUE);
}

pochetnyi::FactorialContainer::reverseIterator pochetnyi::FactorialContainer::rbegin() const
{
  return std::make_reverse_iterator(begin());
}

pochetnyi::FactorialContainer::reverseIterator pochetnyi::FactorialContainer::rend() const
{
  return std::make_reverse_iterator(end());
}
