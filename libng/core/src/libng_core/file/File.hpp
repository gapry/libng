#pragma once

#include <libng_core/encoding/UtfUtil.hpp>
#include <libng_core/exception/error.hpp>
#include <libng_core/file/File.hpp>
#include <libng_core/file/FilePath.hpp>
#include <libng_core/file/FileSize.hpp>
#include <libng_core/file/FileStream.hpp>
#include <libng_core/file/MemMapFile.hpp>
#include <libng_core/libcxx/fixed_vector.hpp>
#include <libng_core/libcxx/limits.hpp>
#include <libng_core/libcxx/span.hpp>
#include <libng_core/libcxx/string_view.hpp>
#include <libng_core/libcxx/type_make.hpp>
#include <libng_core/libcxx/vector.hpp>
#include <libng_core/log/log.hpp>
#include <libng_core/platform/os.hpp>

namespace libng {

struct File {
  File() = delete;

  static bool exists(StrView filename);
  static void rename(StrView oldName, StrView newName);

  static void writeBytes(StrView filename, ByteSpan buf);
  static void writeText(StrView filename, StrView text);

  static char writeFile(StrView filename,       //
                        ByteSpan data,          //
                        bool createDir,         //
                        bool logResult = true); //
  static char writeFile(StrView filename,       //
                        StrView data,           //
                        bool createDir,         //
                        bool logResult = true); //

  static char writeFileIfChanged(StrView filename,          //
                                 StrView data,              //
                                 bool createDir,            //
                                 bool logResult   = true,   //
                                 bool logNoChange = false); //
  static char writeFileIfChanged(StrView filename,          //
                                 ByteSpan data,             //
                                 bool createDir,            //
                                 bool logResult   = true,   //
                                 bool logNoChange = false); //

  static void readFile(StrView filename, Vector<u8>& outData);

  template<size_t N>
  static void readFile(StrView filename, Vector_<u8, N>& outData);

  template<size_t N>
  static void readFile(StrView filename, String_<N>& outData);

private:
  template<class T>
  static void _readFile(StrView filename, T& outData);
};

template<class T>
LIBNG_INLINE void File::_readFile(StrView filename, T& outData) {
  FileStream fs;
  fs.openRead(filename);

  FileSize size = fs.fileSize();
  if (size > libng::numeric_limits<size_t>::max()) {
    throw LIBNG_ERROR("{}\n", "file is too large");
  }
  outData.resize(static_cast<size_t>(size));

  Span<u8> span(reinterpret_cast<u8*>(outData.data()), outData.size());
  fs.readBytes(span);
}

LIBNG_INLINE void File::readFile(StrView filename, Vector<u8>& outData) {
  _readFile(filename, outData);
}

template<size_t N>
LIBNG_INLINE void File::readFile(StrView filename, Vector_<u8, N>& outData) {
  _readFile(filename, outData);
}

template<size_t N>
LIBNG_INLINE void File::readFile(StrView filename, String_<N>& outData) {
  _readFile(filename, outData);
}

LIBNG_INLINE char File::writeFile(StrView filename, ByteSpan data, bool createDir, bool logResult) {
  char op = '+'; // Issue

  auto realPath = FilePath::RealPath(filename);
  if (File::exists(realPath)) {
    op = 'U'; // Issue
  }

  if (logResult) {
    LIBNG_LOG("[{}] path = {}, size = {}\n", op, realPath, data.size());
  }

  if (createDir) {
    auto dir = FilePath::DirName(realPath);
    if (dir.size()) {
      Directory::create(dir);
    }
  }
  writeBytes(realPath, data);
  return op;
}

LIBNG_INLINE char File::writeFile(StrView filename, StrView data, bool createDir, bool logResult) {
  auto bsData = ByteSpan_make(data);
  return writeFile(filename, bsData, createDir, logResult);
}

LIBNG_INLINE void File::writeBytes(StrView filename, ByteSpan buf) {
  libng::FileStream fstream;
  fstream.openWrite(filename, true);
  fstream.writeBytes(buf);
}

LIBNG_INLINE void File::writeText(StrView filename, StrView text) {
  writeBytes(filename, ByteSpan_make(text));
}

LIBNG_INLINE char File::writeFileIfChanged(StrView filename,   //
                                           ByteSpan data,      //
                                           bool createDir,     //
                                           bool logResult,     //
                                           bool logNoChange) { //
  char op = '+';                                               // Issue

  auto realPath = FilePath::RealPath(filename);

  if (exists(realPath)) {
    MemMapFile mapFile;
    mapFile.open(realPath);
    if (mapFile.span() == data) {
      op = '='; // Issue
    } else {
      op = 'U'; // Issue
    }
  }

  if (logResult) {
    if (op != '=' || logNoChange) {
      LIBNG_LOG("[{}] path = {}, size = {}\n", op, realPath, data.size());
    }
  }

  if (op == '=') {
    return op;
  }

  return writeFile(realPath, data, createDir, false);
}

LIBNG_INLINE char File::writeFileIfChanged(StrView filename,   //
                                           StrView data,       //
                                           bool createDir,     //
                                           bool logResult,     //
                                           bool logNoChange) { //
  auto byteSpan = ByteSpan_make(data);
  return writeFileIfChanged(filename, byteSpan, createDir, logResult, logNoChange);
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
