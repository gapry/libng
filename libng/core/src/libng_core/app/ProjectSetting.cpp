#include <libng_core/app/ProjectSetting.hpp>
#include <libng_core/file/Directory.hpp>
#include <libng_core/log/log.hpp>

namespace libng {

ProjectSettings* ProjectSettings::instance() {
  static ProjectSettings s;
  return &s;
}

void ProjectSettings::setProjectRoot(StrView path) {
  Directory::setCurrent(path);

  _projectRoot = path;

  auto currentDir = Directory::getCurrent();
  LIBNG_LOG("projectRoot = {}\n", currentDir);
}

StrView ProjectSettings::importedPath() const {
  return "LocalTemp/Imported";
}

} // namespace libng
