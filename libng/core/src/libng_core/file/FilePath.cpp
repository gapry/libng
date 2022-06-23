#include <libng_core/file/FilePath.hpp>

namespace libng {

String FilePath::GetSlash() {
  String slash;
#if LIBNG_IDE_VSC
  slash = "\\";
#elif LIBNG_IDE_VS
  slash = "/";
#endif
  return slash;
}

String FilePath::GetAssetsPath() {
  String path;
#if LIBNG_IDE_VSC
  path = "\\..\\..\\Assets";
#elif LIBNG_IDE_VS
  path  = "/../../../../Assets";
#endif
  return path;
}

String FilePath::GetTestDataPath(const char* const path) {
  String slash    = FilePath::GetSlash();
  String dataPath = Fmt("{0}{1}{0}{2}{0}{3}{0}", slash, "test", "data", path); // Issue
  return dataPath;
}

StrView FilePath::DirName(StrView path) {
  auto* end = path.end();
  if (end == nullptr) {
    return StrView();
  }

  auto* begin = path.begin();
  for (auto* p = end - 1; p >= begin; p--) {
    if (*p == '/' || *p == '\\') {
      return StrView(begin, p - begin);
    }
  }
  return StrView();
}

// clang-format off
bool FilePath::IsRealPath(const StrView& path) {
  // case: path size == 1
	if (path.size() < 1) return false;
	if (path[0] == '/')  return true;

  // case: the path format something like this: C:/
	if (path.size() < 2)                         return false;
	if (std::isalpha(path[0]) && path[1] == ':') return true;  

  // case: reject
  return false;
}
// clang-format on

String FilePath::RealPath(StrView path) {
  if (!path.size()) {
    return String();
  }

  String outStr;

  bool needSlash = false;
  if (IsRealPath(path)) {
    needSlash = (path[0] == '/'); // UNIX path need '/' at beginning
  } else {
    outStr    = Directory::getCurrent();
    needSlash = true;
  }

  StrView p = path;
  while (p.size()) {
    auto s = StringUtil::splitByChar(p, "\\/");
    if (s.first == ".") {
      // skip '.'
    } else if (!s.first.size()) {
      // skip '/'
    } else if (s.first == "..") {
      auto* parent = StringUtil::findCharFromEnd(outStr, "\\/", false);
      if (parent == nullptr) {
        outStr.clear(); // no more parent folder
        return String();
      }
      outStr.resize(parent - outStr.data());
    } else {
      if (needSlash) {
        outStr += '/';
      }
      outStr += s.first;
      needSlash = true;
    }
    p = s.second;
  }
  return outStr;
}

} // namespace libng