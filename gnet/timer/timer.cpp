#include "timer/timer.hpp"

auto gnet::timer::sleep(int sec) -> void {
#ifdef GNET_OS_WINDOWS
  Sleep(sec * 1000);
#else
  sleep(sec);
#endif
}
