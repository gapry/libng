#pragma once

#include <libng_core/encoding/UtfUtil.hpp>
#include <libng_core/exception/error.hpp>
#include <libng_core/file/FileAccess.hpp>
#include <libng_core/file/FileMode.hpp>
#include <libng_core/file/FileShareMode.hpp>
#include <libng_core/file/FileSize.hpp>
#include <libng_core/libcxx/span.hpp>
#include <libng_core/libcxx/string.hpp>
#include <libng_core/libcxx/string_view.hpp>
#include <libng_core/platform/os.hpp>
#include <libng_core/types/noncopyable.hpp>

namespace libng {

class FileStream : NonCopyable {
public:
#if LIBNG_OS_WINDOWS
  using NativeFd = ::HANDLE;

  static const NativeFd kInvalid() {
    return INVALID_HANDLE_VALUE;
  }
#else
  using NativeFd = int;

  static const NativeFd kInvalid() {
    return -1;
  }
#endif

  ~FileStream() {
    close();
  }

  bool isOpened() const {
    return _fd != kInvalid;
  }

  void openRead(StrView filename);
  void openAppend(StrView filename);
  void openWrite(StrView filename, bool truncate);

  void open(StrView filename, FileMode mode, FileAccess access, FileShareMode shareMode);
  void close();
  void flush();

  FileSize fileSize();
  void setFileSize(FileSize newSize);

  FileSize getPos();
  void setPosFromBegin(FileSize pos);
  void setPosFromEnd(FileSize pos);

  void readBytes(Span<u8> data);
  void writeBytes(ByteSpan data);

  const String& filename() const {
    return _filename;
  }

  NativeFd nativeFd() {
    return _fd;
  }

private:
  void _ensure_fd() {
    if (_fd == kInvalid()) {
      TempString errMsg;
#if defined(LIBNG_OS_WINDOWS)
      errMsg = "invalid file handle";
#else
      errMsg = "invalid file descriptor";
#endif
      throw LIBNG_ERROR("{}\n", errMsg);
    }
  }

  String _filename;

  NativeFd _fd = kInvalid;
};

} // namespace libng
