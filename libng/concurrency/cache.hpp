#pragma once

#include "noncopyable.hpp"

namespace libng {

class cache : public libng::noncopyable<cache> {
public:
  cache() = default;

  ~cache() = default;
};

} // namespace libng
