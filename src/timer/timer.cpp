#include "timer/timer.h"

void gnet::timer::sleep(int sec) {
#ifdef _WIN32
  Sleep(sec * 1000);
#else
  sleep(sec);
#endif
}
