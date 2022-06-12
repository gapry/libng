#pragma once

#include <libng_core/app/Platforms.hpp>

namespace libng {

class ConsoleApp : public Platforms {
public:
  void run(int argc, char** argv);

protected:
  virtual void onRun(int argc, char** argv) = 0;

  void listArgv(int argc, char** argv);
};

} // namespace libng