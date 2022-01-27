#include "functor.hpp"
#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>

pochetnyi::Functor::Functor() :
  min_(0),
  max_(0),
  numOfPositive_(0),
  numOfNegative_(0),
  sumOfOdd_(0),
  sumOfEven_(0),
  first_(0),
  isFirstEqualLast_(false),
  size_(0)
{}

void pochetnyi::Functor::operator()(int val)
{
  if (size_ == 0)
  {
    first_ = min_ = max_ = val;
  }

  min_ = std::min(val, min_);
  max_ = std::max(val, max_);

  if (val < 0)
  {
    numOfNegative_++;
  }
  else if (val > 0)
  {
    numOfPositive_++;
  }

  if (val % 2 == 0)
  {
    sumOfEven_ += val;
  }
  else
  {
    sumOfOdd_ += val;
  }

  isFirstEqualLast_ = (first_ == val);
  size_++;
}

namespace pochetnyi
{
  std::ostream &operator<<(std::ostream &out, const Functor &functor)
  {
    if (functor.size_ == 0)
    {
      out << NO_DATA;
      return out;
    }

    long double mean = (static_cast<long double>(functor.sumOfEven_) + static_cast<long double>(functor.sumOfOdd_)) / functor.size_;
    const char *isEqual = functor.isFirstEqualLast_ ? "yes" : "no";
    out << "Max: " << functor.max_ << "\nMin: " << functor.min_ << "\nMean: " << mean << "\nPositive: "
        << functor.numOfPositive_ << "\nNegative: " << functor.numOfNegative_ << "\nOdd Sum: " << functor.sumOfOdd_
        << "\nEven Sum: " << functor.sumOfEven_ << "\nFirst/Last Equal: " << isEqual;

    return out;
  }
}
