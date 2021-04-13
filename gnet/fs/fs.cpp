#include "fs/fs.hpp"

namespace gnet {

fs::~fs() {
  this->close();
}

#ifdef GNET_OS_WINDOWS
auto fs::open(char const* const filename) -> void {
}

auto fs::read(void) -> void {
}

auto fs::write(void) -> void {
}

auto fs::close(void) -> void {
}
#endif

#if defined(GNET_OS_LINUX) || defined(GNET_OS_FREEBSD)
auto fs::open(char const* const filename) -> void {
}

auto fs::read(void) -> void {
}

auto fs::write(void) -> void {
}

auto fs::close(void) -> void {
}

#endif

} // namespace gnet
