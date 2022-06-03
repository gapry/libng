#pragma once

#include <types/noncopyable.hpp>

namespace libng {

class JSONLexer : public NonCopyable {
public:
  void nextChar();
};

} // namespace libng