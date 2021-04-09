#pragma once

#include "noncopyable.hpp"

namespace gnet {

  class cache: public gnet::noncopyable<cache> {
    public:
      cache() = default;

      ~cache() = default;
  }

}
