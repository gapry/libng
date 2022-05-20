#pragma once

#include <file/FileStream.hpp>
#include <platform/os.hpp>
#include <types/noncopyable.hpp>
#include <libcxx/util/util.hpp>
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

  Span<const u8> span() const {
    return _span;
  }

  operator Span<const u8>() {
    return _span;
  }

  const String& filename() const {
    return _fs.filename();
  }

private:
  FileStream _fs;

#if LIBNG_OS_WINDOWS
  ::HANDLE _mapping = nullptr; // Issue: Warning it's null, not INVALID_HANDLE_VALUE for memory mapping
#endif
  Span<const u8> _span;
};

} // namespace libng
