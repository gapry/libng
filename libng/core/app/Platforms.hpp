#pragma once

#include <types/noncopyable.hpp>
#include <libcxx/string.hpp>

namespace libng {

class Platforms : public NonCopyable {
public:
  String getExecutableFilename();
};

} // namespace libng