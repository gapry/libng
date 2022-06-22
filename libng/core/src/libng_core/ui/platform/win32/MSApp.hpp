#pragma once

#include <libng_core/platform/os.hpp>
#include <libng_core/ui/BaseApp.hpp>

#if LIBNG_OS_WINDOWS

namespace libng {

class MSApp : public BaseApp {
  using Base = BaseApp;

public:
  MSApp();

  ~MSApp();

  MSG _win32_msg;

protected:
  virtual String onGetExecutableFilename() override;

  virtual String onGetCurrentDir() override;

  virtual void onSetCurrentDir(StrView dir) override;

  virtual void onCreate(CreateDesc& desc) override;

  virtual void onRun() override;

  virtual void onQuit() override;
};

} // namespace libng

#endif