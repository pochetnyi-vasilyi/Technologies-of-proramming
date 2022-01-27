#include "stream-guard.hpp"
#include <istream>

pochetnyi::StreamGuard::StreamGuard(std::istream &input) :
  stream_(input),
  flags_(input.flags())
{}

pochetnyi::StreamGuard::~StreamGuard()
{
  stream_.setf(flags_);
}
