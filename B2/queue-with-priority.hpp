#ifndef QUEUE_WITH_PRIORITY_HPP
#define QUEUE_WITH_PRIORITY_HPP

#include <list>
#include <stdexcept>
#include <string>

namespace pochetnyi
{
  template<typename T>
  class QueueWithPriority
  {
  public:
    enum ElementPriority
    {
      LOW,
      NORMAL,
      HIGH
    };

    void putElement(const T &element, ElementPriority priority);

    template<typename F>
    void popElement(const F &function);
    void accelerate();
    bool isEmpty() const;

  private:
    std::list<T> lowQueue_;
    std::list<T> normalQueue_;
    std::list<T> highQueue_;
  };

  template<typename T>
  void QueueWithPriority<T>::putElement(const T &element, ElementPriority priority)
  {
    switch (priority)
    {
      case LOW:
        lowQueue_.push_back(element);
        break;
      case NORMAL:
        normalQueue_.push_back(element);
        break;
      case HIGH:
        highQueue_.push_back(element);
        break;
      default:
        throw std::invalid_argument("Invalid priority!");
    }
  }

  template<typename T>
  template<typename F>
  void QueueWithPriority<T>::popElement(const F &function)
  {
    if (!highQueue_.empty())
    {
      function(highQueue_.front());
      highQueue_.pop_front();
    }
    else if (!normalQueue_.empty())
    {
      function(normalQueue_.front());
      normalQueue_.pop_front();
    }
    else if (!lowQueue_.empty())
    {
      function(lowQueue_.front());
      lowQueue_.pop_front();
    }
    else
    {
      throw std::runtime_error("<EMPTY>\n");
    }
  }

  template<typename T>
  void QueueWithPriority<T>::accelerate()
  {
    highQueue_.splice(highQueue_.end(), lowQueue_);
  }

  template<typename T>
  bool QueueWithPriority<T>::isEmpty() const
  {
    return highQueue_.empty() && normalQueue_.empty() && lowQueue_.empty();
  }
}

#endif
