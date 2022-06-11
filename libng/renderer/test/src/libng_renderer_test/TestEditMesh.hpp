#pragma once

#include <libng_core/log/log.hpp>
#include <libng_core/types/function.hpp>
#include <libng_render/mesh/EditMesh.hpp>
#include <libng_test/unit_test/UnitTestBase.hpp>

namespace libng {

class TestEditMesh : public UnitTestBase {
private:
  void testMeshPos() {
    LIBNG_LOG("{}", __LIBNG_PRETTY_FUNCTION__);
  }

public:
  void onVerify() {
    testMeshPos();
  }
};

} // namespace libng
