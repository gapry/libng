#pragma once

#include <libng_core/libcxx/string.hpp>
#include <libng_core/libcxx/string_view.hpp>
#include <libng_core/types/noncopyable.hpp>

namespace libng {

struct ProjectSettings : public NonCopyable {
  static ProjectSettings* instance();

  void setProjectRoot(StrView path);

  StrView importedPath() const;

  const String& projectRoot() const {
    return _projectRoot;
  }

private:
  String _projectRoot;
};

} // namespace libng