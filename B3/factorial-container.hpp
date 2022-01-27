#ifndef FACTORIAL_CONTAINER
#define FACTORIAL_CONTAINER

#include <iterator>

namespace pochetnyi
{
  namespace detail
  {
    constexpr unsigned int getFactorial(size_t index)
    {
      unsigned int result = 1;
      for (size_t i = 2; i <= index; i++)
      {
        result *= i;
      }
      return result;
    }
  }

  static const size_t START = 1;
  static const size_t END = 11;

  class FactorialIterator : public std::iterator<std::bidirectional_iterator_tag, unsigned int>
  {
  public:
    friend class FactorialContainer;

    FactorialIterator();
    FactorialIterator(size_t index);
    FactorialIterator &operator++();
    FactorialIterator &operator--();
    FactorialIterator operator++(int);
    FactorialIterator operator--(int);
    bool operator==(const FactorialIterator &rhs) const;
    bool operator!=(const FactorialIterator &rhs) const;
    const unsigned int &operator*() const;
    const unsigned int* operator->() const;

  private:
    size_t pos_;
    unsigned int value_;
    static constexpr unsigned int END_VALUE = detail::getFactorial(END);

    FactorialIterator(size_t pos, unsigned int value);
  };

  class FactorialContainer
  {
  public:
    friend class FactorialIterator;
    typedef std::reverse_iterator<FactorialIterator> reverseIterator;

    FactorialContainer() = default;
    FactorialIterator begin() const;
    FactorialIterator end() const;
    reverseIterator rbegin() const;
    reverseIterator rend() const;
  };
}
#endif
