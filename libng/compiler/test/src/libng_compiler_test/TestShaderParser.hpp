#pragma once

#include <fmt/core.h>
#include <libng_compiler/shader/ShaderParser.hpp>
#include <libng_test/unit_test/UnitTestBase.hpp>

namespace libng {

class TestShaderParser : public UnitTestBase, ShaderParser {
private:
  void testParseIdentifier() {
    if (!_parseIdentifier()) {
      fmt::print("{}\n", "Parse ID is false");
    }
  }

public:
  void onVerify() {
    testParseIdentifier();
  }
};

} // namespace libng
