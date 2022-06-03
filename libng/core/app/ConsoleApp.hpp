#pragma once

#include <app/BaseApp.hpp>

namespace libng {

class ConsoleApp : public BaseApp {
public:
  void run();

protected:
  virtual void onRun() = 0;
};

} // namespace libng