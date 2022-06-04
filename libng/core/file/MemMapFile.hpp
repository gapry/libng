#pragma once

#include <file/FileStream.hpp>
#include <exception/error.hpp>
#include <platform/os.hpp>
#include <types/number.hpp>
#include <types/noncopyable.hpp>
#include <libcxx/span.hpp>
#include <libcxx/string.hpp>

namespace libng {

class MemMapFile : public NonCopyable {
public:
  ~MemMapFile() {
    close();
  }

  void open(StrView filename);

  void close();

  const u8* data() const {
    return _span.data();
  }

  size_t size() const {
    return _span.size();
  }

  ByteSpan span() const {
    return _span;
  }

  operator ByteSpan() {
    return _span;
  }

  const String& filename() const {
    return _filestream.filename();
  }

private:
  FileStream _filestream;

#if LIBNG_OS_WINDOWS
  ::HANDLE _mapping = nullptr; // Issue: Warning it's null, not INVALID_HANDLE_VALUE for memory mapping
#endif

  ByteSpan _span;
};

} // namespace libng
