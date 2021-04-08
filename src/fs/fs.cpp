#include "fs.hpp"

gnet::fs::~fs() {
  this->close();
}

#ifdef GNET_OS_WINDOWS
auto gnet::fs::open(void) -> void {
}

auto gnet::fs::read(void) -> void {
}

auto gnet::fs::write(void) -> void {
}

auto gnet::fs::close(void) -> void {
}
#endif

#if defined(GNET_OS_LINUX) || defined(GNET_OS_FREEBSD)
auto gnet::fs::open(void) -> void {
}

auto gnet::fs::read(void) -> void {
}

auto gnet::fs::write(void) -> void {
}

auto gnet::fs::close(void) -> void {
}

#endif
