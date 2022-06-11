#pragma once

#include <libng_core/types/noncopyable.hpp>
#include <libng_core/libcxx/string.hpp>

namespace libng {

class Platforms : public NonCopyable {
public:
  String getExecutableFilename();
};

} // namespace libng