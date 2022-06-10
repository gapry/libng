#pragma once

#include <fmt/core.h>
#include <test/unit_test/base.hpp>

#include <compiler/shader/ShaderParser.hpp>

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