#include <fmt/core.h>
#include <exception/error.hpp>
#include <memory/util.hpp>
#include <types/number.hpp>
#include <ui/platform/win32/MSWindow.hpp>
#include <ui/platform/win32/Win32Util.hpp>

namespace libng {

MSWindow::MSWindow() {
}

MSWindow::~MSWindow() {
}

void MSWindow::onCreate(CreateDesc& desc) {
  Base::onCreate(desc);

  const wchar_t* clsName = L"MSWindow";

  auto hInstance   = ::GetModuleHandle(nullptr);
  WNDCLASSEX wc    = {};
  wc.cbSize        = sizeof(wc);
  wc.style         = CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc   = &s_wndProc;
  wc.cbClsExtra    = 0;
  wc.cbWndExtra    = 0;
  wc.hInstance     = hInstance;
  wc.hIcon         = LoadIcon(hInstance, IDI_APPLICATION);
  wc.hCursor       = LoadCursor(hInstance, IDC_ARROW);
  wc.hbrBackground = nullptr;
  wc.lpszMenuName  = nullptr;
  wc.lpszClassName = clsName;
  wc.hIconSm       = LoadIcon(hInstance, IDI_APPLICATION);

  if (!desc.closeButton) {
    wc.style |= CS_NOCLOSE;
  }

  DWORD dwStyle   = 0;
  DWORD dwExStyle = WS_EX_ACCEPTFILES;

  if (desc.alwaysOnTop) {
    dwExStyle |= WS_EX_TOPMOST;
  }

  switch (desc.type) {
    case CreateDesc::Type::ToolWindow:
    case CreateDesc::Type::NormalWindow: {
      dwStyle |= WS_OVERLAPPED | WS_SYSMENU;
      // clang-format off
      if (desc.closeButton) dwStyle |= WS_SYSMENU;
      if (desc.resizable)   dwStyle |= WS_THICKFRAME;
      if (desc.titleBar)    dwStyle |= WS_CAPTION;
      if (desc.minButton)   dwStyle |= WS_MINIMIZEBOX;
      if (desc.maxButton)   dwStyle |= WS_MAXIMIZEBOX;
      // clang-format on
    } break;
    case CreateDesc::Type::PopupWindow: {
      dwStyle |= WS_POPUP | WS_BORDER;
    } break;
    default: LIBNG_ASSERT(false); break;
  }

  if (desc.type == CreateDesc::Type::ToolWindow) {
    dwExStyle |= WS_EX_TOOLWINDOW;
  }

  WNDCLASSEX tmpWc;
  bool registered = (0 != ::GetClassInfoEx(hInstance, clsName, &tmpWc));
  if (!registered) {
    if (!::RegisterClassEx(&wc)) {
      throw LIBNG_ERROR("[error] RegisterClassEx is failed");
    }
  }

  auto rect = desc.rect;
  if (desc.centerToScreen) {
    auto screenSize = Vec2f((float)GetSystemMetrics(SM_CXSCREEN), (float)GetSystemMetrics(SM_CYSCREEN));
    rect.pos        = (screenSize - rect.size) / 2;
  }

  _hwnd = ::CreateWindowEx(dwExStyle,
                           clsName,
                           clsName,
                           dwStyle,
                           (int)desc.rect.x,
                           (int)desc.rect.y,
                           (int)desc.rect.w,
                           (int)desc.rect.h,
                           nullptr,
                           nullptr,
                           hInstance,
                           this);
  if (!_hwnd) {
    throw LIBNG_ERROR("[Error] Can't create MSWindow");
  }
  ShowWindow(_hwnd, SW_SHOW);
}

void MSWindow::onSetWindowTitle(StrView title) {
  if (!_hwnd) {
    return;
  }

  TempStringW tmp; // Issue: = UtfUtil::toStringW(title);
  ::SetWindowText(_hwnd, tmp.c_str());
}

void MSWindow::onDrawNeeded() {
  ::InvalidateRect(_hwnd, nullptr, false);
}

LRESULT MSWindow::_handleWin32Event(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
  return ::DefWindowProc(hwnd, msg, wParam, lParam);
}

LRESULT WINAPI MSWindow::s_wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
  switch (msg) {
    case WM_CREATE: {
      auto cs        = reinterpret_cast<CREATESTRUCT*>(lParam);
      auto* thisObj  = static_cast<This*>(cs->lpCreateParams);
      thisObj->_hwnd = hwnd;
      ::SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)thisObj);
    } break;
    case WM_DESTROY: {
      if (auto* thisObj = s_getThis(hwnd)) {
        ::SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR) nullptr);
        thisObj->_hwnd = nullptr;
        libng_delete(thisObj);
      }
    } break;
    case WM_PAINT: {
      PAINTSTRUCT ps;
      BeginPaint(hwnd, &ps);
      if (auto* thisObj = s_getThis(hwnd)) {
        thisObj->onDraw();
      }
      EndPaint(hwnd, &ps);
      return 0;
    } break;
    case WM_CLOSE: {
      if (auto* thisObj = s_getThis(hwnd)) {
        thisObj->onCloseButton();
        return 0;
      }
    } break;
    case WM_SIZE: {
      if (auto* thisObj = s_getThis(hwnd)) {
        RECT clientRect;
        ::GetClientRect(hwnd, &clientRect);
        Rect2f newClientRect = Win32Util::toRect2f(clientRect);
        thisObj->onClientRectChanged(newClientRect);
        return 0;
      }
    } break;
    case WM_ACTIVATE: {
      if (auto* thisObj = s_getThis(hwnd)) {
        u16 a = LOWORD(wParam);
        switch (a) {
          case WA_ACTIVE: thisObj->onActive(true); break;
          case WA_CLICKACTIVE: thisObj->onActive(true); break;
          case WA_INACTIVE: thisObj->onActive(false); break;
          default: break;
        }
      }
    } break;
    default: {
      if (auto* thisObj = s_getThis(hwnd)) {
        return thisObj->_handleWin32Event(hwnd, msg, wParam, lParam);
      }
    } break;
  }
  return ::DefWindowProc(hwnd, msg, wParam, lParam);
}

LIBNG_INLINE MSWindow* MSWindow::s_getThis(HWND hwnd) {
  return reinterpret_cast<MSWindow*>(::GetWindowLongPtr(hwnd, GWLP_USERDATA));
}

} // namespace libng