#include <libng_core/file/Directory.hpp>
#include <libng_core/file/File.hpp>
#include <libng_core/file/FilePath.hpp>
#include <libng_core/libcxx/fixed_vector.hpp>
#include <libng_core/libcxx/string.hpp>
#include <libng_core/libcxx/vector.hpp>
#include <libng_core/log/log.hpp>
#include <libng_core/types/number.hpp>

#include <libng_test/unit_test/UnitTestBase.hpp>

namespace libng {

class TestFile : public UnitTestBase {
  String getTestDataPath(const char* const folder) {
    String currentPath = libng::Directory::getCurrent();
    String slash       = libng::FilePath::GetSlash();
    String dataPath    = Fmt("{0}{1}{0}{2}{0}{3}{0}", slash, "test", "data", folder); // Issue
    currentPath.append(dataPath);
    return currentPath;
  }

public:
  void test_exists() {
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

  void test_rename() {
    auto path      = getTestDataPath("Json");
    String oldName = Fmt("{}{}", path, "sample.json");
    String newName = Fmt("{}{}", path, "dataset.json");

    File::rename(oldName, newName);
    File::rename(newName, oldName);
  }

  void test_write_bytes() {
    auto path   = getTestDataPath("Json");
    String file = Fmt("{}{}", path, "sample.json");

    const char* const test_data = "{}\n\r"; // Issue
    ByteSpan buff(reinterpret_cast<const u8*>(test_data), sizeof(test_data));
    File::writeBytes(file, buff);
  }

  void test_write_file() {
    auto path   = getTestDataPath("Json");
    String file = Fmt("{}{}", path, "config.json");

    {
      const char* const data = "[]\n\r"; // Issue
      File::writeFile(file, data, true, true);
    }

    {
      const char* const test_data = "{}\n\r"; // Issue
      ByteSpan buff(reinterpret_cast<const u8*>(test_data), sizeof(test_data));
      File::writeFile(file, buff, true, true);
    }
  }

  void test_write_file_if_change() {
    auto path   = getTestDataPath("Json");
    String file = Fmt("{}{}", path, "config.json");

    {
      const char* const test_data = "{}\n\r"; // Issue
      ByteSpan buff(reinterpret_cast<const u8*>(test_data), sizeof(test_data));
      File::writeFileIfChanged(file, buff, true, true);
    }

    {
      const char* const data = "[]\n\r"; // Issue
      File::writeFileIfChanged(file, data, true, true);
    }
  }

  void test_read_file() {
    auto path   = getTestDataPath("Json");
    String file = Fmt("{}{}", path, "config.json");

    {
      Vector<u8> data;
      File::readFile(file, data);
      LIBNG_LOG("Vector size = {}\n", data.size());
    }
    {
      Vector_<u8, 16> data;
      File::readFile(file, data);
      LIBNG_LOG("fixed vector size = {}\n", data.size());
    }
    {
      String_<16> data;
      File::readFile(file, data);
      LIBNG_LOG("fixed string size = {}\n", data.size());
    }
  }
};

} // namespace libng

void test_file() {
  LIBNG_TEST_CASE(libng::TestFile, test_exists());
  LIBNG_TEST_CASE(libng::TestFile, test_rename());
  LIBNG_TEST_CASE(libng::TestFile, test_write_bytes());
  LIBNG_TEST_CASE(libng::TestFile, test_write_file());
  LIBNG_TEST_CASE(libng::TestFile, test_write_file_if_change());
  LIBNG_TEST_CASE(libng::TestFile, test_read_file());
}