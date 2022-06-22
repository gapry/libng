#include <libng_core/libcxx/fmt.hpp>
#include <libng_core/libcxx/string.hpp>
#include <libng_core/libcxx/unique_ptr.hpp>
#include <libng_core/log/log.hpp>
#include <libng_core/types/function.hpp>

#include <libng_test/unit_test/UnitTestBase.hpp>

namespace libng {

class test_packet_chat {
public:
  String username;
  String hostname;

  test_packet_chat() {
    username = "user1";
    hostname = "host1";
    version  = "v1.0";

    LIBNG_LOG("{}\n", __LIBNG_PRETTY_FUNCTION__);
  }

  // Issue
  test_packet_chat(String name, String host)
    : version("v2.0") {
    username = name;
    hostname = host;

    LIBNG_LOG("{}\n", __LIBNG_PRETTY_FUNCTION__);
  }

  ~test_packet_chat() {
    username.clear();
    hostname.clear();
    version.clear();

    LIBNG_LOG("{}\n", __LIBNG_PRETTY_FUNCTION__);
  }

  auto onFormat(fmt::format_context& ctx) const {
    return fmt::format_to(ctx.out(), "[username: {}, hostname: {}, version: {}]", username, hostname, version);
  }

private:
  String version;
};

LIBNG_FORMATTER(test_packet_chat);

} // namespace libng

namespace libng::libcxx {

class test_unique_ptr : public UnitTestBase {
public:
  void test_ctor_and_dtor() {
    auto ptr1 = libng::libcxx::unique_ptr<libng::test_packet_chat>(new libng::test_packet_chat());
    auto ptr2 = libng::libcxx::make_unique<libng::test_packet_chat>(libng::String("user2"), libng::String("host2"));
  }

  void test_operator() {
    auto pkt1 = libng::libcxx::unique_ptr<libng::test_packet_chat>(new libng::test_packet_chat());
    auto pkt2 = libng::libcxx::make_unique<libng::test_packet_chat>(libng::String("user2"), libng::String("host2"));

    LIBNG_LOG("packet1 = {}\n", fmt::format("{}", *pkt1));
    LIBNG_LOG("packet2 = {}\n", fmt::format("{}", *pkt2));

    LIBNG_LOG("pkt1 host     = {}\n", pkt1->hostname);
    LIBNG_LOG("pkt1 username = {}\n", pkt1->username);

    LIBNG_LOG("pkt2 host     = {}\n", pkt2->hostname);
    LIBNG_LOG("pkt2 username = {}\n", pkt2->username);
  }
};

} // namespace libng::libcxx

void test_unique_ptr() {
  // using namespace libng; // issue
  LIBNG_TEST_CASE(libng::libcxx::test_unique_ptr, test_ctor_and_dtor());
  LIBNG_TEST_CASE(libng::libcxx::test_unique_ptr, test_operator());
}
