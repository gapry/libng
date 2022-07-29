#pragma once

#include <libng_core/math/Geometry/Line3.hpp>
#include <libng_core/math/Geometry/Rect2.hpp>
#include <libng_core/math/Matrix/Mat4.hpp>
#include <libng_core/math/Vector/Vec2.hpp>
#include <libng_core/math/Vector/Vec3.hpp>
#include <libng_core/math/Vector/Vec4.hpp>

namespace libng::math {

template<class T>
struct Ray3 {
private:
  using Vec2  = Vec2<T>;
  using Vec3  = Vec3<T>;
  using Vec4  = Vec4<T>;
  using Mat4  = Mat4<T>;
  using Rect2 = Rect2<T>;
  using Line3 = Line3<T>;

public:
  Vec3 origin, dir;

  Ray3() = default;

  Ray3(const Vec3& origin_, const Vec3& dir_)
    : origin(origin_)
    , dir(dir_) {
  }

  constexpr static Ray3 s_zero() {
    return Ray3(Vec3::s_zero(), Vec3::s_zero());
  }

  static Ray3 s_unprojectFromInvMatrix(const Vec2& screenPos, const Mat4& invMat, const Rect2& viewport);

  struct HitTestResult {
    T distance = math::inf<T>();
    Vec3 point;
    Vec3 normal;

    bool hasResult() const {
      return distance != math::inf<T>();
    }
  };

  bool getClosestPoint(Vec3& outPoint, const Vec3& inPoint) const;

  bool getClosestPoint(Vec3& outPoint, const Line3& line, T minOnLine = 0, T maxOnLine = 1) const;
};

using Ray3f = Ray3<float>;
using Ray3d = Ray3<double>;

template<class T>
Ray3<T> Ray3<T>::s_unprojectFromInvMatrix(const Vec2& screenPos, const Mat4& invMat, const Rect2& viewport) {
  auto pt = screenPos;

  Vec3 p0(pt, 0);
  Vec3 p1(pt, 1);

  auto v0 = invMat.unprojectPointFromInv(p0, viewport);
  auto v1 = invMat.unprojectPointFromInv(p1, viewport);

  Ray3 o;
  o.origin = v0;
  o.dir    = (v1 - v0).normalize();
  return o;
}

template<class T>
bool Ray3<T>::getClosestPoint(Vec3& outPoint, const Vec3& inPoint) const {
  auto v   = inPoint - origin;
  auto t   = v.dot(dir);
  outPoint = (t <= 0) ? origin : origin + dir * t;
  return true;
}

template<class T>
bool Ray3<T>::getClosestPoint(Vec3& outPoint, const Line3& line, T minOnLine, T maxOnLine) const {
  auto da = line.end - line.start;
  auto db = dir;
  auto dc = origin - line.start;

  auto ab = da.cross(db);
  if (ab.equals0()) {
    return false;
  }

  auto s   = dc.cross(db).dot(da.cross(db)) / ab.sqrLength();
  s        = math::clamp<T>(s, minOnLine, maxOnLine);
  outPoint = line.start + da * s;
  return true;
}

} // namespace libng::math