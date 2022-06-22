#include <libng_core/file/Directory.hpp>
#include <libng_core/file/File.hpp>
#include <libng_core/file/FilePath.hpp>
#include <libng_core/libcxx/string.hpp>
#include <libng_core/log/log.hpp>

#include <libng_test/unit_test/UnitTestBase.hpp>

namespace libng {

class TestFile : public UnitTestBase {
  String getTestDataPath(const char* const folder) {
    String currentPath = libng::Directory::getCurrent();
    String slash       = libng::FilePath::getSlash();
    String dataPath    = Fmt("{0}{1}{0}{2}{0}{3}{0}", slash, "test", "data", folder); // Issue
    currentPath.append(dataPath);
    return currentPath;
  }

public:
  void testExists() {
    auto onCheck = [](const String& path, const char* const name) -> void {
      String filename = Fmt("{}{}", path, name);
      bool ret        = libng::File::exists(filename);
      LIBNG_LOG("filename = {}\n", filename);
      LIBNG_LOG("ret      = {}\n", ret ? "true" : "false");
    };

    auto currentPath = getTestDataPath("Json");
    onCheck(currentPath, "test_write.json");
    onCheck(currentPath, "sample.json");
    onCheck(currentPath, "");
  }

  void testRename() {
    auto path      = getTestDataPath("Json");
    String oldName = Fmt("{}{}", path, "sample.json");
    String newName = Fmt("{}{}", path, "dataset.json");

    File::rename(oldName, newName);
    File::rename(newName, oldName);
  }
};

} // namespace libng

void test_file() {
  LIBNG_TEST_CASE(libng::TestFile, testExists());
  LIBNG_TEST_CASE(libng::TestFile, testRename());
}