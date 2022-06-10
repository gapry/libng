#pragma once

#include <types/noncopyable.hpp>
#include <libcxx/string.hpp>

namespace libng {

class BaseApp : public NonCopyable {
public:
  String getExecutableFilename();
};

} // namespace libng