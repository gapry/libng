#pragma once

#include <libng_core/input/UIEventModifier.hpp>
#include <libng_core/platform/os.hpp>
#include <libng_core/types/function.hpp>
#include <libng_core/ui/BaseWindow.hpp>

#if LIBNG_OS_WINDOWS

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

  bool _handleNativeUIMouseEvent(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

  UIEventModifier _getWin32Modifier();

  static LRESULT WINAPI s_wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

  LIBNG_INLINE static This* s_getThis(HWND hwnd);
};

} // namespace libng

#endif