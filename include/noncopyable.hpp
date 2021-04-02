#pragma once

namespace gnet {

template <class T>
class noncopyable {
protected:
  noncopyable() = default;

  ~noncopyable() noexcept = default;

private:
  noncopyable(noncopyable const&) = delete;

  auto operator=(T const&) -> void = delete;
};

} // namespace gnet
