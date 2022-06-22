#pragma once

#include <libng_core/encoding/UtfUtil.hpp>
#include <libng_core/exception/error.hpp>
#include <libng_core/file/FileStream.hpp>
#include <libng_core/libcxx/span.hpp>
#include <libng_core/libcxx/string_view.hpp>
#include <libng_core/platform/os.hpp>

namespace libng {

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
  libng::FileStream fstream;
  fstream.openWrite(filename, true);
  fstream.writeBytes(buf);
}

LIBNG_INLINE void File::writeText(StrView filename, StrView buf) {
}

#if defined(LIBNG_OS_WINDOWS)

LIBNG_INLINE bool File::exists(StrView filename) {
  TempStringW filenameW;
  UtfUtil::convert(filenameW, filename);

  // https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-getfileattributesw
  DWORD dwAttrib = ::GetFileAttributes(filenameW.c_str());

  // https://docs.microsoft.com/en-us/windows/win32/fileio/file-attribute-constants
  bool ret = (dwAttrib != INVALID_FILE_ATTRIBUTES &&   //
              !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY)); //
  return ret;
}

LIBNG_INLINE void File::rename(StrView oldName, StrView newName) {
  TempStringW oldNameW, newNameW;
  UtfUtil::convert(oldNameW, oldName);
  UtfUtil::convert(newNameW, newName);

  // https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/rename-wrename
  if (int ret = ::_wrename(oldNameW.c_str(), newNameW.c_str()); 0 != ret) {
    throw LIBNG_ERROR("rename file {} -> {} is failed", oldNameW, newNameW);
  }
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