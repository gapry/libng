#pragma once

#include <libng_core/math/Geometry/Line3.hpp>
#include <libng_core/math/Geometry/Rect2.hpp>
#include <libng_core/math/Graphics/Ray3.hpp>
#include <libng_core/math/Maths.hpp>
#include <libng_core/math/Matrix/Mat4.hpp>
#include <libng_core/math/Number/Quaternion.hpp>
#include <libng_core/math/Vector/Vec2.hpp>
#include <libng_core/math/Vector/Vec3.hpp>
#include <libng_core/math/Vector/Vec4.hpp>

namespace libng::math {

// clang-format off

template<class T>
struct Camera3 {
  using Vec2  = Vec2<T>;
  using Vec3  = Vec3<T>;
  using Vec4  = Vec4<T>;
  using Mat4  = Mat4<T>;
  using Quat4 = Quat4<T>;
  using Rect2 = Rect2<T>;
  using Ray3  = Ray3<T>;

  void pan  (T x, T y);
  void orbit(T x, T y);
  void move (T x, T y, T z);
  void move (const Vec3& v) { move(v.x, v.y, v.z); }

  void dolly(T z);

  void setPos(T x, T y, T z) { setPos(Vec3(x,y,z)); }
  void setAim(T x, T y, T z) { setAim(Vec3(x,y,z)); }
  void setUp (T x, T y, T z) { setUp (Vec3(x,y,z)); }

  void setPos(const Vec3& pos) { _pos = pos; }
  void setAim(const Vec3& aim) { _aim = aim; }
  void setUp (const Vec3& up)  { _up  = up;  }

  const Vec3& pos() const { return _pos; }
  const Vec3& aim() const { return _aim; }
  const Vec3& up () const { return _up;  }

  void setViewport(const Rect2& v) { _viewport = v;    }
  const Rect2& viewport() const    { return _viewport; }

  Ray3 getRay(const Vec2& screenPos) const;

  Mat4 viewMatrix()     const;
  Mat4 projMatrix()     const;
  Mat4 viewProjMatrix() const { return projMatrix() * viewMatrix(); }

private:  
  float _fov      = 50.0f;
  float _nearClip = 0.1f;
  float _farClip  = 10000.0f;

  Rect2 _viewport;

  Vec3 _pos {150, 150, 200};
  Vec3 _aim {0,   0,   0};
  Vec3 _up  {0,   1,   0};
};

// clang-format on

template<class T>
void Camera3<T>::pan(T x, T y) {
  auto v     = _aim - _pos;
  auto right = _up.cross(v).normalize();

  auto q = Quat4::s_eulerY(x) * Quat4::s_angleAxis(y, right);
  v      = q * v;
  _up    = q * _up;
  _aim   = _pos + v;
}

template<class T>
void Camera3<T>::orbit(T x, T y) {
  auto v     = _pos - _aim;
  auto right = _up.cross(v).normalize();

  auto q = Quat4::s_angleAxis(y, right) * Quat4::s_eulerY(x);
  v      = q * v;
  _up    = q * _up;
  _pos   = _aim + v;
}

template<class T>
void Camera3<T>::move(T x, T y, T z) {
  auto v     = _aim - _pos;
  auto dir   = v.normalize();
  auto right = _up.cross(dir);

  auto t = right * x + _up * y + dir * z;
  _pos += t;
  _aim += t;
}

template<class T>
void Camera3<T>::dolly(T z) {
  auto v   = _pos - _aim;
  auto dir = v.normalize();
  auto d   = v.length();
  d += z;
  d = math::max(d, static_cast<T>(0.001));

  _pos = _aim + dir * d;
}

template<class T>
Ray3<T> Camera3<T>::getRay(const Vec2& screenPos) const {
  return Ray3::s_unprojectFromInvMatrix(screenPos, viewProjMatrix().inverse(), _viewport);
}

template<class T>
Mat4<T> Camera3<T>::viewMatrix() const {
  return Mat4::s_lookAt(_pos, _aim, _up);
}

template<class T>
Mat4<T> Camera3<T>::projMatrix() const {
  T aspect = _viewport.h != 0 ? _viewport.w / _viewport.h : T(0);
  return Mat4::s_perspective(math::radians(_fov), aspect, _nearClip, _farClip);
}

using Camera3f = Camera3<float>;
using Camera3d = Camera3<double>;

} // namespace libng::math