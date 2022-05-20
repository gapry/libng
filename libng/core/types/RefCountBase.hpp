#pragma once

#include <types/noncopyable.hpp>
#include <atomic>

namespace libng {

class RefCountBase : public NonCopyable {
public:
  std::atomic_int _refCount = 0;
};

} // namespace libng