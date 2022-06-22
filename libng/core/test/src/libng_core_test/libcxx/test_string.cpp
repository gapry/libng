#include <libng_core/libcxx/fmt.hpp>
#include <libng_core/libcxx/string.hpp>
#include <libng_core/log/log.hpp>
#include <libng_core/types/function.hpp>

#include <libng_test/unit_test/UnitTestBase.hpp>

namespace libng::libcxx {

class test_string : public UnitTestBase {
public:
  void test_ctor_and_dtor() {
    // libng::libcxx::string s0;    // Issue;
    // libng::libcxx::string s1();  // Issue;
    libng::libcxx::string s2("I go to school by bus!");
    libng::libcxx::string s3(s2);

    LIBNG_LOG("s2 = {}\n", s2);
    LIBNG_LOG("s3 = {}\n", s3);
  }

  void test_operator() {
    libng::libcxx::string s0("I go to school by bus!");
    libng::libcxx::string s1 = s0;
    LIBNG_LOG("s0 = {}\n", s0);
    LIBNG_LOG("s1 = {}\n", s1);
  }

  void test_c_str() {
    libng::libcxx::string s0("I go to school by bus!");
    char* s1 = s0.c_str();
    LIBNG_LOG("s0 = {}\n", s0);
    LIBNG_LOG("s1 = {}\n", s1);
  }

  void test_ref_cnt() {
    libng::libcxx::string s0("I go to school by bus!");
    auto s1 = s0;
    auto s2 = s1;
    auto s3(s2);
    fmt::print("reference count = {}\n", s0.ref_cnt());
    fmt::print("reference count = {}\n", s1.ref_cnt());
    fmt::print("reference count = {}\n", s2.ref_cnt());
    fmt::print("reference count = {}\n", s3.ref_cnt());
  }

  void test_char() {
    libng::libcxx::string s0("I go to school by bus!");
    auto s1 = s0;

    s1[0] = 'i';
    fmt::print("s0 = {}\n", s0);
    fmt::print("s1 = {}\n", s1);

    char* ptr = &s1[2];
    fmt::print("ptr = {}\n", *ptr);
  }
};

} // namespace libng::libcxx

void test_string() {
  LIBNG_TEST_CASE(libng::libcxx::test_string, test_ctor_and_dtor());
  LIBNG_TEST_CASE(libng::libcxx::test_string, test_operator());
  LIBNG_TEST_CASE(libng::libcxx::test_string, test_c_str());
  LIBNG_TEST_CASE(libng::libcxx::test_string, test_ref_cnt());
  LIBNG_TEST_CASE(libng::libcxx::test_string, test_char());
}
