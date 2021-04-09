#pragma once

#include "gspan.hpp"
#include "noncopyable.hpp"
#include "platform/type.hpp"

class deserializer : public noncopyable<noncopyable> {
  u8 const* m_data = nullptr;

public:
  explicit deserializer(gnet::span<u8 const> data)
    : m_data(data.data()) {
  }

  ~deserializer() = default;
}
