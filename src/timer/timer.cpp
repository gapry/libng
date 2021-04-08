#include "timer/timer.hpp"

void gnet::timer::sleep(int sec) {
#ifdef GNET_OS_WINDOWS
  Sleep(sec * 1000);
#else
  sleep(sec);
#endif
}
