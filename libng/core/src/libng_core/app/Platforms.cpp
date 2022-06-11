#include <libng_core/app/Platforms.hpp>
#include <libng_core/platform/os.hpp>
#include <libng_core/types/function.hpp>
#include <libng_core/exception/error.hpp>
#include <libng_core/encoding/UtfUtil.hpp>

namespace libng {

#if LIBNG_OS_WINDOWS

String Platforms::getExecutableFilename() {
  wchar_t chunk[MAX_PATH + 1];

  // https://docs.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-getmodulefilenamew
  if (!::GetModuleFileName(nullptr, chunk, MAX_PATH)) {
    LIBNG_ERROR("{}", __LIBNG_PRETTY_FUNCTION__);
  }

  String filename = UtfUtil::toString(chunk);
  return filename;
}

#endif

} // namespace libng