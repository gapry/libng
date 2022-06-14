// #include <fmt/core.h>
#include <iostream>

#include <libng_core/log/log.hpp>
#include <libng_core/types/function.hpp>
#include <libng_core/libcxx/fmt.hpp>
#include <libng_core/libcxx/string.hpp>
#include <libng_core/serializer/json/json_serializer.hpp>
#include <libng_core/serializer/json/json_deserializer.hpp>

#include <libng_render/material/ShaderInfo.hpp>

#include <libng_test/unit_test/UnitTestBase.hpp>

namespace libng {

class test_json : public UnitTestBase {
public:
  void test_ctor() {
    Json dataset = R"({"position": "SV_POSITION", "color": "COLOR"})"_json;
    // fmt::print("{}\n", dataset); // Issue
    std::cout << dataset << "\n";
    json_serializer json_se(dataset);
    json_deserializer json_de(dataset);
  }

  void test_to_value() {
    Json dataset;
    json_serializer json_se(dataset);
    json_deserializer json_de(dataset);

    uint8_t sender = 10;
    uint8_t recver = 0;

    json_se.io(sender);
    fmt::print("sender = {}, recver = {}\n", sender, recver);

    json_de.io(recver);
    fmt::print("sender = {}, recver = {}\n", sender, recver);
  }

  void test_io_shader_info() {
    Json dataset;
    auto obj = Json::object();
    std::cout << "dataset = " << dataset << "\n";
    std::cout << "obj     = " << obj << "\n";

    ShaderInfo src_info;
    ShaderInfo dst_info;

    fmt::print("{}\n", "-----------");

    json_serializer json_se(dataset);
    json_se.io(src_info);

    fmt::print("{}\n", "-----------");

    json_deserializer json_de(dataset);
    json_de.io(dst_info);

    fmt::print("{}\n", "-----------");
  }

  void test_str_view() {
    Json dataset;
    json_serializer json_se(dataset);
    json_deserializer json_de(dataset);

    String send_msg = "I go to school by bus !!!";
    String recv_msg;

    json_se.io(send_msg);
    fmt::print("send msg = {}\n", send_msg);
    fmt::print("recv msg = {}\n", recv_msg);

    json_de.io(recv_msg);
    fmt::print("send msg = {}\n", send_msg);
    fmt::print("recv msg = {}\n", recv_msg);
  }
};

} // namespace libng

void test_json() {
  LIBNG_TEST_CASE(libng::test_json, test_ctor());
  LIBNG_TEST_CASE(libng::test_json, test_to_value());
  LIBNG_TEST_CASE(libng::test_json, test_io_shader_info());
  LIBNG_TEST_CASE(libng::test_json, test_str_view());
}
