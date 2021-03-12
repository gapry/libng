#ifndef __GNET_STRING_H__
#define __GNET_STRING_H__

#include <string>

namespace gnet {

class string {
  using string_t = std::string;

public:
  string() = default;

  ~string() = default;

  string_t m_string;
};

} // namespace gnet

#endif
