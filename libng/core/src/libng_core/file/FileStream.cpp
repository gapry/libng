#include <libng_core/file/FileStream.hpp>

namespace libng {

void FileStream::openRead(StrView filename) {
  open(filename, FileMode::OpenExists, FileAccess::Read, FileShareMode::Read);
}

void FileStream::openAppend(StrView filename) {
  open(filename, FileMode::OpenOrCreate, FileAccess::ReadWrite, FileShareMode::Read);
  setPosFromEnd(0);
}

void FileStream::openWrite(StrView filename, bool truncate) {
  open(filename, FileMode::OpenOrCreate, FileAccess::ReadWrite, FileShareMode::Read);
  if (truncate) {
    setFileSize(0);
  }
}

#if defined(LIBNG_OS_WINDOWS)

void FileStream::open(StrView filename, FileMode mode, FileAccess access, FileShareMode shareMode) {
  close();

  _filename = filename;

  DWORD create_flags = 0;
  DWORD access_flags = 0;
  DWORD share_flags  = 0;
  // clang-format off
  switch (mode) {
    case FileMode::CreateNew      : create_flags |= CREATE_NEW; break;
    case FileMode::OpenExists     : create_flags |= OPEN_EXISTING; break;
    case FileMode::OpenOrCreate   : create_flags |= OPEN_ALWAYS; break;
  }
  switch (access) {
    case FileAccess::Read         : access_flags |= GENERIC_READ; break;
    case FileAccess::ReadWrite    : access_flags |= GENERIC_READ | GENERIC_WRITE; break;
    case FileAccess::WriteOnly    : access_flags |= GENERIC_WRITE; break;
  }
  switch (shareMode) {
    case FileShareMode::None      : break;
    case FileShareMode::Read      : share_flags |= FILE_SHARE_READ; break;
    case FileShareMode::ReadWrite : share_flags |= FILE_SHARE_READ | FILE_SHARE_WRITE; break;
    case FileShareMode::Write     : share_flags |= FILE_SHARE_WRITE; break;
  }
  // clang-format on

  TempStringW filenameW;
  UtfUtil::convert(filenameW, filename);

  _fd = ::CreateFile(filenameW.c_str(),     //
                     access_flags,          //
                     share_flags,           //
                     nullptr,               //
                     create_flags,          //
                     FILE_ATTRIBUTE_NORMAL, //
                     nullptr);              //
  if (_fd == kInvalid()) {
    DWORD err = ::GetLastError();
    // clang-format off
    switch (err) {
      case ERROR_FILE_NOT_FOUND    : throw LIBNG_ERROR("file not found");
      case ERROR_PATH_NOT_FOUND    : throw LIBNG_ERROR("path not found");
      case ERROR_FILE_EXISTS       : throw LIBNG_ERROR("file doesn't exists");
      case ERROR_ALREADY_EXISTS    : throw LIBNG_ERROR("file already exists");
      case ERROR_ACCESS_DENIED     : throw LIBNG_ERROR("access denied");
      case ERROR_SHARING_VIOLATION : throw LIBNG_ERROR("sharing violation");
      default                      : throw LIBNG_ERROR("open file error");
    }
    // clang-format on
  }
}

void FileStream::close() {
  if (!isOpened()) {
    return;
  }

  BOOL ret = ::CloseHandle(_fd);
  if (!ret) {
    throw LIBNG_ERROR("close file error");
  }
  _fd = kInvalid();
}

// https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-readfile
void FileStream::readBytes(Span<u8> data) {
  _ensure_fd();

  if (data.size() <= 0) {
    return;
  }

  if (data.size() >= UINT32_MAX) {
    throw LIBNG_ERROR("file read");
  }

  DWORD dwSize = static_cast<DWORD>(data.size());
  DWORD result = 0;

  BOOL ret = ::ReadFile(_fd,         //
                        data.data(), //
                        dwSize,      //
                        &result,     //
                        nullptr);    //
  if (!ret) {
    DWORD e = ::GetLastError();
    switch (e) {
      case ERROR_LOCK_VIOLATION: throw LIBNG_ERROR("file lock violation");
    }
    throw LIBNG_ERROR("file read");
  }
}

// https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-writefile
void FileStream::writeBytes(ByteSpan data) {
  _ensure_fd();

  if (data.size() <= 0) {
    return;
  }

  if (data.size() >= UINT32_MAX) {
    throw LIBNG_ERROR("file read");
  }

  DWORD dwSize = static_cast<DWORD>(data.size());
  DWORD result = 0;

  BOOL ret = ::WriteFile(_fd,         //
                         data.data(), //
                         dwSize,      //
                         &result,     //
                         nullptr);    //
  if (!ret) {
    throw LIBNG_ERROR("file write");
  }
}

FileSize FileStream::fileSize() {
  _ensure_fd();

  DWORD high = 0;
  DWORD low  = ::GetFileSize(_fd, &high);
  if (low == INVALID_FILE_SIZE) {
    throw LIBNG_ERROR("file size");
  }

  auto fileSize = static_cast<FileSize>(high) << 32 | low;
  return fileSize;
}

// https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-setendoffile
void FileStream::setFileSize(FileSize newSize) {
  _ensure_fd();

  FileSize oldPos = getPos();
  setPosFromBegin(newSize);
  ::SetEndOfFile(_fd);

  if (oldPos < newSize) {
    setPosFromBegin(oldPos);
  }
}

// https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-setfilepointer
FileSize FileStream::getPos() {
  _ensure_fd();
  LONG high = 0;
  LONG low  = ::SetFilePointer(_fd, 0, &high, FILE_CURRENT);
  if (low < 0 || high < 0) {
    throw LIBNG_ERROR("{}", "The file position isn't correct!");
  }
  auto pos = static_cast<FileSize>(low) | static_cast<FileSize>(high) << 32;
  return pos;
}

void FileStream::setPosFromBegin(FileSize pos) {
  _ensure_fd();
  LONG high = static_cast<LONG>(pos >> 32);
  LONG low  = static_cast<LONG>(pos);
  ::SetFilePointer(_fd, low, &high, FILE_BEGIN);
}

void FileStream::setPosFromEnd(FileSize pos) {
  _ensure_fd();
  LONG high = static_cast<LONG>(pos >> 32);
  LONG low  = static_cast<LONG>(pos);
  ::SetFilePointer(_fd, low, &high, FILE_END);
}

#elif defined(LIBNG_OS_LINUX) || defined(LIBNG_OS_MACOS) || defined(LIBNG_OS_FREEBSD)

void FileStream::open(StrView filename, FileMode mode, FileAccess access, FileShareMode shareMode) {
}

void FileStream::close() {
}

void FileStream::readBytes(Span<u8> data) {
}

void FileStream::writeBytes(ByteSpan data) {
}

FileSize FileStream::fileSize() {
  return 0;
}

void FileStream::setFileSize(FileSize newSize) {
}

FileSize FileStream::getPos() {
  return 0;
}

void FileStream::setPosFromBegin(FileSize pos) {
}

void FileStream::setPosFromEnd(FileSize pos) {
}

#else

void FileStream::open(StrView filename, FileMode mode, FileAccess access, FileShareMode shareMode) {
}

void FileStream::close() {
}

void FileStream::readBytes(Span<u8> data) {
}

void FileStream::writeBytes(ByteSpan data) {
}

FileSize FileStream::fileSize() {
  return 0;
}

void FileStream::setFileSize(FileSize newSize) {
}

FileSize FileStream::getPos() {
  return 0;
}

void FileStream::setPosFromBegin(FileSize pos) {
}

void FileStream::setPosFromEnd(FileSize pos) {
}

#endif

} // namespace libng
