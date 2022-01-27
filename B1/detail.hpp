#ifndef DETAIL_HPP
#define DETAIL_HPP

#include <iostream>
#include <vector>
#include <cstring>

namespace pochetnyi
{
    namespace detail
    {
      enum Direction
      {
        ASCENDING,
        DESCENDING
      };

      Direction getDirection(const char* direction);
    }

    template<template <typename T> typename AccessWay, typename T>
    void sort(T &container, detail::Direction direction)
    {
      bool sortType = direction == detail::Direction::ASCENDING;
      for (typename AccessWay<T>::value_type i = AccessWay<T>::getBegin(container); i != AccessWay<T>::getEnd(container); i++)
      {
        for (typename AccessWay<T>::value_type j = i; j != AccessWay<T>::getEnd(container); j++)
        {
          if (( (sortType) && (AccessWay<T>::getValue(container, i) > AccessWay<T>::getValue(container, j)) )
              || ( (!sortType) && (AccessWay<T>::getValue(container, i) < AccessWay<T>::getValue(container, j)) ))
          {
            std::swap(AccessWay<T>::getValue(container, i), AccessWay<T>::getValue(container, j));
          }
        }
      }
    }

    template<typename T>
    void print(const T &container)
    {
      if (container.begin() != container.end())
      {
        for (typename T::const_iterator iter = container.cbegin(); iter != container.cend(); iter++)
        {
          std::cout << *iter << " ";
        }
        std::cout << '\n';
      }
    }

    template<typename T>
    class IndexAccess
    {
    public:
      typedef typename T::size_type value_type;

      static value_type getBegin(const T&);
      static typename T::reference getValue(T &container, value_type n);
      static value_type getEnd(const T &container);
    };

    template<typename T>
    class AtAccess
    {
    public:
      typedef typename T::size_type value_type;

      static value_type getBegin(const T&);
      static typename T::reference getValue(T &container, value_type n);
      static value_type getEnd(const T &container);
    };

    template<typename T>
    class IteratorAccess
    {
    public:
      typedef typename T::iterator value_type;

      static value_type getBegin(T &container);
      static typename T::reference getValue(T&, value_type n);
      static value_type getEnd(T &container);
    };

    template<typename T>
    typename IndexAccess<T>::value_type IndexAccess<T>::getBegin(const T&)
    {
      return 0;
    }

    template<typename T>
    typename T::reference IndexAccess<T>::getValue(T &container, value_type n)
    {
      return container[n];
    }

    template<typename T>
    typename IndexAccess<T>::value_type IndexAccess<T>::getEnd(const T &container)
    {
      return container.size();
    }

    template<typename T>
    typename AtAccess<T>::value_type AtAccess<T>::getBegin(const T&)
    {
      return 0;
    }

    template<typename T>
    typename T::reference AtAccess<T>::getValue(T &container, value_type n)
    {
      return container.at(n);
    }

    template<typename T>
    typename AtAccess<T>::value_type AtAccess<T>::getEnd(const T &container)
    {
      return container.size();
    }

    template<typename T>
    typename IteratorAccess<T>::value_type IteratorAccess<T>::getBegin(T &container)
    {
      return container.begin();
    }

    template<typename T>
    typename T::reference IteratorAccess<T>::getValue(T&, value_type n)
    {
      return *n;
    }

    template<typename T>
    typename IteratorAccess<T>::value_type IteratorAccess<T>::getEnd(T &container)
    {
      return container.end();
    }
}
#endif //DETAIL_HPP
