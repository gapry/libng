#include <platform/os.hpp>
#include <file/FileStream.hpp>
#include <exception/error.hpp>
#include <libcxx/util.hpp>
#include <file/MemMapFile.hpp>

namespace libng {

#if LIBNG_OS_WINDOWS

void MemMapFile::open(StrView filename) {
  close();

  _fs.openRead(filename);

  if (_fs.fileSize() >= SIZE_T_MAX)
    throw LIBNG_ERROR("memmap file size too larget");

  auto size = static_cast<size_t>(_fs.fileSize());
  if (size <= 0)
    return;

  _mapping = ::CreateFileMapping(_fs.nativeFd(), nullptr, PAGE_READONLY, 0, 0, nullptr);
  if (!_mapping) {
    throw LIBNG_ERROR("memmap");
  }

  auto* data = reinterpret_cast<u8*>(::MapViewOfFile(_mapping, FILE_MAP_READ, 0, 0, 0));
  if (!data) {
    throw LIBNG_ERROR("memmap");
  }

  _span = Span<const u8>(data, size);
}

void MemMapFile::close() {
  if (_span.size() <= 0)
    return;
  ::UnmapViewOfFile(_span.data());

  if (_mapping) {
    ::CloseHandle(_mapping);
    _mapping = nullptr;
  }

  _span = Span<const u8>();
  _fs.close();
}

#endif

} // namespace libng