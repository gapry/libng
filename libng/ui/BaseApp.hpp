#pragma once

#include <types/noncopyable.hpp>

namespace libng {

class BaseApp : public NonCopyable {
public:
  class CreateDesc {
  public:
  };

  int run(CreateDesc& desc);

  void quit(int returnCode);

  virtual void willQuit();

protected:
  virtual void onCreate(CreateDesc& desc);

  virtual void onRun();

  virtual void onQuit();

  int _exitCode = 0;
};

} // namespace libng