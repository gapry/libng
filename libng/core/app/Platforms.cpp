#include <app/Platforms.hpp>
#include <platform/os.hpp>
#include <types/function.hpp>
#include <exception/error.hpp>
#include <encoding/UtfUtil.hpp>

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