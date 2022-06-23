#include <libng_core/file/MemMapFile.hpp>

namespace libng {

#if defined(LIBNG_OS_WINDOWS)

// https://docs.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-createfilemappingw
void MemMapFile::open(StrView filename) {
  close();

  _filestream.openRead(filename);
  if (_filestream.fileSize() >= SIZE_T_MAX) {
    throw LIBNG_ERROR("{}", "File size too larget\n");
  }

  auto size = static_cast<size_t>(_filestream.fileSize());
  if (size <= 0) {
    return;
  }

  _mapping = ::CreateFileMapping(_filestream.nativeFd(), // obj
                                 nullptr,                // default security attributes
                                 PAGE_READONLY,          // permission
                                 0,                      // high size
                                 0,                      // low size
                                 nullptr);               // create obj without the name
  if (!_mapping) {
    throw LIBNG_ERROR("{}", "Can't CreateFileMapping\n");
  }

  auto* data = reinterpret_cast<u8*>(::MapViewOfFile(_mapping,      // obj
                                                     FILE_MAP_READ, // permission
                                                     0,             // high offset
                                                     0,             // low offset
                                                     0));           // bytes to map
  if (!data) {
    throw LIBNG_ERROR("{}", "Can't MapViewOfFile\n");
  }

  _span = ByteSpan(data, size);
}

// https://docs.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-unmapviewoffile
void MemMapFile::close() {
  if (_span.size() <= 0) {
    return;
  }

  ::UnmapViewOfFile(_span.data());

  if (_mapping) {
    ::CloseHandle(_mapping);
    _mapping = nullptr;
  }

  _span = ByteSpan();
  _filestream.close();
}

#elif defined(LIBNG_OS_LINUX) || defined(LIBNG_OS_MACOS) || defined(LIBNG_OS_FREEBSD)

void MemMapFile::open(StrView filename) {
  close();
}

void MemMapFile::close() {
}

#else

void MemMapFile::open(StrView filename) {
  close();
}

void MemMapFile::close() {
}

#endif

} // namespace libng
