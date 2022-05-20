#pragma once

#include <ui/BaseApp.hpp>
#include <platform/os.hpp>

#if LIBNG_OS_WINDOWS

#include <Windows.h>
#include <Windowsx.h>

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