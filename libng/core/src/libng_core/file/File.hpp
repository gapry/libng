#pragma once

#include <libng_core/libcxx/string_view.hpp>
#include <libng_core/libcxx/span.hpp>
#include <libng_core/exception/error.hpp>
#include <libng_core/types/number.hpp>
#include <libng_core/platform/os.hpp>

namespace libng {

using FileSize = u64;

enum class FileMode
{
  CreateNew,
  OpenExists,
  OpenOrCreate,
};

enum class FileAccess
{
  Read,
  ReadWrite,
  WriteOnly,
};

enum class FileShareMode
{
  None,
  Read,
  Write,
  ReadWrite,
};

struct File {
  File() = delete;

  static bool exists(StrView filename);
  static void rename(StrView src, StrView dst);

  static void writeBytes(StrView filename, ByteSpan buf);
  static void writeText(StrView filename, StrView buf);

  static char writeFile(StrView filename, ByteSpan data, bool createDir, bool logResult = true);
  static char writeFile(StrView filename, StrView data, bool createDir, bool logResult = true);
};

LIBNG_INLINE char File::writeFile(StrView filename, ByteSpan data, bool createDir, bool logResult) {
  return ' ';
}

LIBNG_INLINE char File::writeFile(StrView filename, StrView data, bool createDir, bool logResult) {
  return ' ';
}

LIBNG_INLINE void File::writeBytes(StrView filename, ByteSpan buf) {
}

LIBNG_INLINE void File::writeText(StrView filename, StrView buf) {
}

#if defined(LIBNG_OS_WINDOWS)

LIBNG_INLINE bool File::exists(StrView filename) {
  return false;
}

LIBNG_INLINE void File::rename(StrView src, StrView dst) {
}

#elif defined(LIBNG_OS_LINUX) || defined(LIBNG_OS_MACOS) || defined(LIBNG_OS_FREEBSD)

bool File::exists(StrView filename) {
  LIBNG_ERROR("[{}] {}\n", __LIBNG_PRETTY_FUNCTION__, "Unimplemented");
  return false;
}

void File::rename(StrView src, StrView dst) {
  LIBNG_ERROR("[{}] {}\n", __LIBNG_PRETTY_FUNCTION__, "Unimplemented");
}

#else

bool File::exists(StrView filename) {
  LIBNG_ERROR("[{}] {}\n", __LIBNG_PRETTY_FUNCTION__, "Unsupported");
  return false;
}

void File::rename(StrView src, StrView dst) {
  LIBNG_ERROR("[{}] {}\n", __LIBNG_PRETTY_FUNCTION__, "Unsupported");
}

#endif

} // namespace libng