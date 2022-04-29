#pragma once

#include <platform/os.hpp>
#include <ui/BaseWindow.hpp>
#include <types/function.hpp>

#if LIBNG_OS_WINDOWS

#include <Windows.h>
#include <Windowsx.h>

namespace libng {

class MSWindow : public BaseWindow {
  using This = MSWindow;
  using Base = BaseWindow;

public:
  MSWindow();

  ~MSWindow();

  virtual void onCreate(CreateDesc& desc) override;

  virtual void onSetWindowTitle(StrView title) override;

  virtual void onDrawNeeded() override;

  HWND _hwnd;

private:
  LRESULT _handleWin32Event(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

  static LRESULT WINAPI s_wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

  LIBNG_INLINE static This* s_getThis(HWND hwnd);
};

} // namespace libng

#endif