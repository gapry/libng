#pragma once

#include "gvector.hpp"
#include "platform/endian.hpp"
#include "platform/type.hpp"

namespace gnet {

class serializer : public noncopyable<serializer> {
  vector<u8>* m_buff = nullptr;

public:
  explicit serializer(vector<u8>& buff)
    : m_buff(&buff) {
  }

  ~serializer() = default;
}

} // namespace gnet
