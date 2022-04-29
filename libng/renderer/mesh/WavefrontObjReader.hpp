#pragma once

#include <math/Tuple/Tuple2.hpp>
#include <math/Tuple/Tuple3.hpp>
#include <third_party/eastl/eastl.hpp>
#include <mesh/EditMesh.hpp>

namespace libng {

class WavefrontObjReader {
public:
  using Mesh = EditMesh;

  void loadFile(const char* const filename, Mesh* const mesh);

private:
  void _readLine(const char* p);

  void _readFace(const char* p);

  const char* _readFaceVertex(const char* p);

  Vector<Tuple3f> _v;
  Vector<Tuple2f> _vt;
  Vector<Tuple3f> _vn;

  int _lineNumber = 0;

  Mesh* _mesh = nullptr;
};

} // namespace libng