#ifndef __GNET_VERCTOR_H__
#define __GNET_VERCTOR_H__

#include <vector>

namespace gnet {

template <typename T>
class vector {
  using vector_t = std::vector<T>;

public:
  vector() = default;

  ~vector() = default;

  vector_t m_vec;
};

} // namespace gnet

#endif
