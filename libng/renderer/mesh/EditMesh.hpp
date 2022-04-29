#pragma once

#include <types/noncopyable.hpp>
#include <types/number.hpp>
#include <third_party/eastl/eastl.hpp>
#include <math/Color.hpp>
#include <math/Tuple2.hpp>
#include <math/Tuple3.hpp>

namespace libng {

class EditMesh : public NonCopyable {
public:
  static const u8 kUvCountMax = 4;

  Vector<Tuple3f> pos;
  Vector<Tuple2f> uv[kUvCountMax];
  Vector<Color4b> color;

  Vector<Tuple3f> normal;
  Vector<Tuple3f> tangent;
  Vector<Tuple3f> binormal;

  void loadObjFile(StrView filename);
};

} // namespace libng