#include "timer/timer.hpp"

auto libng::timer::sleep(int sec) -> void {
#ifdef LIBNG_OS_WINDOWS
  Sleep(sec * 1000);
#else
  sleep(sec);
#endif
}
