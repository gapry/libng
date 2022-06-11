#pragma once

#include <libng_core/types/noncopyable.hpp>

namespace libng {

class JSONLexer : public NonCopyable {
public:
  void nextChar();
};

} // namespace libng