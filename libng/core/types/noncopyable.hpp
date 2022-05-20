#pragma once

namespace libng {

class NonCopyable {
public:
  NonCopyable() = default;

private:
  // NonCopyable(NonCopyable&&) = delete;

  NonCopyable(const NonCopyable&) = delete;

  void operator=(const NonCopyable&) = delete;
};

} // namespace libng
