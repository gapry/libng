#include <libng_core/types/number.hpp>
#include <libng_core/log/log.hpp>
#include <libng_core/libcxx/string.hpp>
#include <libng_core/libcxx/Span.hpp>
#include <libng_core/file/MemMapFile.hpp>
#include <libng_core/file/Directory.hpp>
#include <libng_core/file/FilePath.hpp>
#include <libng_test/unit_test/UnitTestBase.hpp>

namespace libng {

class TestMemMapFile : public UnitTestBase {
public:
  void test_open() {
    static const char* data = "I go to school by bus!";
    ByteSpan sample(reinterpret_cast<const u8*>(data), sizeof(data));
    LIBNG_LOG("sample = {}\n", sample.data());

    libng::String file = libng::Directory::getCurrent();
    LIBNG_LOG("file = {}\n", file);

    String slash;
#if LIBNG_IDE_VSC
    slash = "\\";
#elif LIBNG_IDE_VS
    slash = "/";
#endif
    String dataPath = Fmt("{}test{}data{}MemMapFile{}", slash, slash, slash, slash);

    file.append(dataPath);
    LIBNG_LOG("file = {}\n", file);

    String filename = Fmt("{}{}", file, "sample.txt");
    LIBNG_LOG("file = {}\n", filename);

    MemMapFile mapFile;
    mapFile.open(filename);

    // LIBNG_TEST_CHECK(mapFile.span() == sample); // Issue
    LIBNG_LOG("mapFile == {}\n", mapFile.span().data());
    LIBNG_LOG("file    == {}\n", filename.data());
  }
};

} // namespace libng

void test_mem_map_file() {
  LIBNG_TEST_CASE(libng::TestMemMapFile, test_open());
}