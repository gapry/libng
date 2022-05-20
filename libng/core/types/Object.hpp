#pragma once

#include <types/RefCountBase.hpp>

namespace libng {

class Object : public RefCountBase {
public:
  virtual ~Object() = default; // Issue: virtual dtor, virtual ctor
};

} // namespace libng