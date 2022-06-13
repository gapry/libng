// #include <fmt/core.h>
#include <iostream>
#include <libng_core/log/log.hpp>
#include <libng_core/types/function.hpp>
#include <libng_core/libcxx/fmt.hpp>
#include <libng_core/serializer/json/json_serializer.hpp>
#include <libng_core/serializer/json/json_deserializer.hpp>
#include <libng_test/unit_test/UnitTestBase.hpp>

namespace libng {

class test_json : public UnitTestBase {
public:
  void test_ctor() {
    Json dataset = R"({"position": "SV_POSITION", "color": "COLOR"})"_json;
    // fmt::print("{}\n", dataset); // Issue
    std::cout << dataset << "\n";
    json_serializer json_se(dataset);
  }

  void test_to_value() {
    Json dataset;
    json_serializer json_se(dataset);

    uint8_t v;
    json_se.io(v);
  }
};

} // namespace libng

void test_json() {
  LIBNG_TEST_CASE(libng::test_json, test_ctor());
  LIBNG_TEST_CASE(libng::test_json, test_to_value());
}
