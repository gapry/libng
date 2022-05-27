#include <file/FilePath.hpp>
#include <file/Directory.hpp>
#include <libcxx/util/UtfUtil.hpp>
#include <exception/error.hpp>

namespace libng {

void Directory::create(StrView path) {
  if (exists(path))
    return;

  auto parent = FilePath::dirname(path);
  if (parent.size()) {
    create(parent);
  }

  _create(path);
}

void Directory::setCurrent(StrView dir) {
  TempStringW tmp = UtfUtil::toStringW(dir);
  ::SetCurrentDirectory(tmp.c_str());
}

String Directory::getCurrent() {
  wchar_t tmp[MAX_PATH + 1];
  if (!::GetCurrentDirectory(MAX_PATH, tmp))
    throw LIBNG_ERROR("GetCurrentDirectory");
  String o = UtfUtil::toString(tmp);
  return o;
}

void Directory::_create(StrView path) {
  TempStringW pathW;
  UtfUtil::convert(pathW, path);
  auto ret = ::CreateDirectory(pathW.c_str(), nullptr);
  if (!ret)
    throw LIBNG_ERROR("create directory {}", pathW);
}

bool Directory::exists(StrView path) {
  TempStringW pathW;
  UtfUtil::convert(pathW, path);

  DWORD dwAttrib = ::GetFileAttributes(pathW.c_str());
  return (dwAttrib != INVALID_FILE_ATTRIBUTES && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

} // namespace libng