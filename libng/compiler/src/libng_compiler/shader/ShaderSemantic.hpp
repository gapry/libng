#pragma once

namespace libng {

class ShaderSemantic {
public:
  template<typename T, typename U>
  bool primitiveType(T lhs, U rhs) {
    return false;
  }

  template<typename T, typename U>
  bool posType(T lhs, U rhs) {
    return false;
  }

  template<typename T, typename U>
  bool colorType(T lhs, U rhs) {
    return false;
  }

  template<typename T, typename U>
  bool normalType(T lhs, U rhs) {
    return false;
  }

  template<typename T, typename U>
  bool biNormalType(T lhs, U rhs) {
    return false;
  }

  template<typename T, typename U>
  bool texType(T lhs, U rhs) {
    return false;
  }
};

} // namespace libng
