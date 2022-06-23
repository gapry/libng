#include <libng_core/file/Directory.hpp>

namespace libng {

void Directory::create(StrView path) {
  if (exists(path)) {
    return;
  }

  auto parent = FilePath::DirName(path);
  if (parent.size()) {
    create(parent);
  }
  _create(path);
}

#if defined(LIBNG_OS_WINDOWS)

void Directory::setCurrent(StrView dir) {
  TempStringW tmp = UtfUtil::toStringW(dir);
  ::SetCurrentDirectory(tmp.c_str());
}

String Directory::getCurrent() {
  wchar_t tmp[MAX_PATH + 1];
  if (!::GetCurrentDirectory(MAX_PATH, tmp)) {
    throw LIBNG_ERROR("GetCurrentDirectory");
  }
  String o = UtfUtil::toString(tmp);
  return o;
}

void Directory::_create(StrView path) {
  TempStringW pathW;
  UtfUtil::convert(pathW, path);
  if (auto ret = ::CreateDirectory(pathW.c_str(), nullptr); !ret) {
    throw LIBNG_ERROR("create directory {}", pathW);
  }
}

bool Directory::exists(StrView path) {
  TempStringW pathW;
  UtfUtil::convert(pathW, path);

  DWORD dwAttrib = ::GetFileAttributes(pathW.c_str());
  return (dwAttrib != INVALID_FILE_ATTRIBUTES &&  //
          (dwAttrib & FILE_ATTRIBUTE_DIRECTORY)); //
}

#elif defined(LIBNG_OS_LINUX) || defined(LIBNG_OS_MACOS) || defined(LIBNG_OS_FREEBSD)

void Directory::setCurrent(StrView dir) {
}

String Directory::getCurrent() {
}

bool Directory::exists(StrView path) {
}

void Directory::_create(StrView path) {
}

#else

void Directory::setCurrent(StrView dir) {
}

String Directory::getCurrent() {
}

bool Directory::exists(StrView path) {
}

void Directory::_create(StrView path) {
}

#endif

} // namespace libng