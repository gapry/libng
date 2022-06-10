#pragma once

#include <app/Platforms.hpp>

namespace libng {

class ConsoleApp : public Platforms {
public:
  void run();

protected:
  virtual void onRun() = 0;
};

} // namespace libng