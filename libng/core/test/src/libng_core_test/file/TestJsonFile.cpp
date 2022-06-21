#include <libng_core/types/number.hpp>
#include <libng_core/log/log.hpp>
#include <libng_core/libcxx/string.hpp>
#include <libng_core/libcxx/Span.hpp>
#include <libng_core/file/JsonFile.hpp>
#include <libng_core/file/Directory.hpp>
#include <libng_core/file/FilePath.hpp>
#include <libng_core/file/JsonFile.hpp>
#include <libng_render/material/ShaderInfo.hpp>
#include <libng_test/unit_test/UnitTestBase.hpp>

namespace libng {

class TestJsonFile : public UnitTestBase {
public:
  void test_write() {
    libng::String path = libng::Directory::getCurrent();
    LIBNG_LOG("path = {}\n", path);

    String slash        = FilePath::getSlash();
    String testDataPath = Fmt("{0}{1}{0}{2}{0}{3}{0}", slash, "test", "data", "JsonFile"); // Issue

    path.append(testDataPath);
    LIBNG_LOG("path = {}\n", path);

    String filename = Fmt("{}{}", path, "test_write.json");
    LIBNG_LOG("the json filename = {}\n", filename);

    ShaderInfo info;
    JsonFile::write(filename, info, false);
  }
};

} // namespace libng

void test_json_file() {
  LIBNG_TEST_CASE(libng::TestJsonFile, test_write());
}