#ifndef FUNCTOR
#define FUNCTOR

#include <vector>
#include <iostream>

namespace pochetnyi
{
  const std::string NO_DATA = "No Data\n";

  class Functor
  {
  public:
    Functor();

    void operator()(int val);
    friend std::ostream &operator<<(std::ostream &out, const Functor &functor);

  private:
    int min_;
    int max_;
    size_t numOfPositive_;
    size_t numOfNegative_;
    long long sumOfOdd_;
    long long sumOfEven_;
    int first_;
    bool isFirstEqualLast_;
    size_t size_;
  };
}

#endif
