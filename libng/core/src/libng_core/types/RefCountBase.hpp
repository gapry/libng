#pragma once

#include <atomic>
#include <libng_core/types/noncopyable.hpp>

namespace libng {

class RefCountBase : public NonCopyable {
public:
  std::atomic_int _refCount = 0;
};

} // namespace libng