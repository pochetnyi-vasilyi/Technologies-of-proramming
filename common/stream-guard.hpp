#ifndef STREAM_GUARD
#define STREAM_GUARD

#include <istream>

namespace pochetnyi
{
  class StreamGuard
  {
  public:
    StreamGuard(std::istream &input);
    ~StreamGuard();

  private:
    std::istream &stream_;
    std::istream::fmtflags flags_;
  };
}

#endif
