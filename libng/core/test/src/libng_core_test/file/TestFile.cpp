#include <libng_core/log/log.hpp>
#include <libng_core/libcxx/string.hpp>
#include <libng_core/file/File.hpp>
#include <libng_core/file/FilePath.hpp>
#include <libng_core/file/Directory.hpp>
#include <libng_test/unit_test/UnitTestBase.hpp>

namespace libng {

class TestFile : public UnitTestBase {
public:
  void test_exists() {
    auto onCheck = [](const String& path, const char* const name) -> void {
      String filename = Fmt("{}{}", path, name);
      bool ret        = libng::File::exists(filename);
      LIBNG_LOG("filename = {}\n", filename);
      LIBNG_LOG("ret      = {}\n", ret ? "true" : "false");
    };

    String currentPath = libng::Directory::getCurrent();
    String slash       = libng::FilePath::getSlash();
    String dataPath    = Fmt("{0}{1}{0}{2}{0}{3}{0}", slash, "test", "data", "Json"); // Issue
    currentPath.append(dataPath);

    onCheck(currentPath, "test_write.json");
    onCheck(currentPath, "sample.json");
    onCheck(currentPath, "");
  }
};

} // namespace libng

void test_file() {
  LIBNG_TEST_CASE(libng::TestFile, test_exists());
}