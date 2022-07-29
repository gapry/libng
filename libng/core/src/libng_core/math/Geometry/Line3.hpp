#pragma once

#include <libng_core/math/Vector/Vec3.hpp>

namespace libng::math {

template<class T>
struct Line3 {
  Line3() = default;

  Line3(const Vec3& start_, const Vec3& end_)
    : start(start_)
    , end(end_) {
  }

  bool getClosestPoint(Vec3& outPoint, const Vec3& inPoint) const;

  T distanceToPoint(const Vec3& pt) const;

  Vec3 start;
  Vec3 end;
};

using Line3f = Line3<float>;
using Line3d = Line3<double>;

} // namespace libng::math