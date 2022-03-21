#include "fs/fs.hpp"

namespace libng {

fs::~fs() {
  this->close();
}

#ifdef LIBNG_OS_WINDOWS
auto fs::open(char const* const filename) -> void {
}

auto fs::read(void) -> void {
}

auto fs::write(void) -> void {
}

auto fs::close(void) -> void {
}
#endif

#if defined(LIBNG_OS_LINUX) || defined(LIBNG_OS_FREEBSD)
auto fs::open(char const* const filename) -> void {
}

auto fs::read(void) -> void {
}

auto fs::write(void) -> void {
}

auto fs::close(void) -> void {
}

#endif

} // namespace libng
