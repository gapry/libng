// #include <fmt/core.h>
#include <iostream>

#include <libng_core/log/log.hpp>
#include <libng_core/types/function.hpp>
#include <libng_core/types/number.hpp>
#include <libng_core/types/enum.hpp>
#include <libng_core/exception/error.hpp>
#include <libng_core/libcxx/fmt.hpp>
#include <libng_core/libcxx/string.hpp>
#include <libng_core/serializer/json/json_serializer.hpp>
#include <libng_core/serializer/json/json_deserializer.hpp>

#include <libng_render/type/RenderDataType.hpp>
#include <libng_render/material/ShaderInfo.hpp>

#include <libng_test/unit_test/UnitTestBase.hpp>

namespace libng {

enum class TestJsonInfo : u8
{
  None,
  PosX,
};

#define TestJsonInfo_ENUM_LIST(E) \
  E(None)                         \
  E(PosX)                         \
  // ----
LIBNG_ENUM_STR_UTIL(TestJsonInfo)

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

    LIBNG_LOG("{}\n", "-----------");

    json_serializer json_se(dataset);
    json_se.io(src_info);

    LIBNG_LOG("{}\n", "-----------");

    json_deserializer json_de(dataset);
    json_de.io(dst_info);

    LIBNG_LOG("{}\n", "-----------");
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

  void test_to_object_member() {
    auto print = [](const char* const sig, const std::pair<f32, f32>& pos) -> void {
      LIBNG_LOG("{} = ({}, {})\n", sig, pos.first, pos.second);
    };

    auto pos = Json::object();

    auto send_pos = std::make_pair<f32, f32>(1.2f, 2.1f);
    auto recv_pos = std::make_pair<f32, f32>(0.0f, 0.0f);

    print(LIBNG_GET_FUNCTION_NAME(send_pos), send_pos);
    print(LIBNG_GET_FUNCTION_NAME(recv_pos), recv_pos);

    json_serializer json_se(pos);
    json_se.named_io("pos_x", send_pos.first);
    json_se.named_io("pos_y", send_pos.second);

    json_deserializer json_de(pos);
    json_de.named_io("pos_x", recv_pos.first);
    json_de.named_io("pos_y", recv_pos.second);

    print(LIBNG_GET_FUNCTION_NAME(send_pos), send_pos);
    print(LIBNG_GET_FUNCTION_NAME(recv_pos), recv_pos);
  }

  void test_array() {
    auto print = [](const Vector_<f32, 16>& dataset) -> void {
      for (auto& data : dataset) {
        fmt::print("{} ", data);
      }
      fmt::print("\n");
    };

    Json storage;
    auto send_dataset = Vector_<f32, 16>();
    auto recv_dataset = Vector_<f32, 16>();

    // send_dataset.resize(4); // Issue
    send_dataset.push_back(1.2f);
    send_dataset.push_back(2.3f);
    send_dataset.push_back(3.4f);
    send_dataset.push_back(4.5f);

    json_serializer json_se(storage);
    json_se.io(send_dataset);

    print(send_dataset);
    print(recv_dataset);

    json_deserializer json_de(storage);
    json_de.io(recv_dataset);

    print(send_dataset);
    print(recv_dataset);
  }

  void test_enum(void) {
    Json storage;

    TestJsonInfo p1 = TestJsonInfo::PosX;
    TestJsonInfo p2;
    // RenderDataType d1 = RenderDataType::Float16;

    json_serializer json_se(storage);
    json_se.io(p1);
    // json_se.io(d1); // Issue: bug as continue io

    json_deserializer json_de(storage);
    json_de.io(p2);
  }
};

} // namespace libng

void test_json() {
  LIBNG_TEST_CASE(libng::test_json, test_ctor());
  LIBNG_TEST_CASE(libng::test_json, test_to_value());
  LIBNG_TEST_CASE(libng::test_json, test_io_shader_info());
  LIBNG_TEST_CASE(libng::test_json, test_str_view());
  LIBNG_TEST_CASE(libng::test_json, test_to_object_member());
  LIBNG_TEST_CASE(libng::test_json, test_array());
  LIBNG_TEST_CASE(libng::test_json, test_enum());
}
