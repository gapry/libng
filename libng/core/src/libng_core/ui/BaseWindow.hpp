#pragma once

#include <libng_core/types/noncopyable.hpp>
#include <libng_core/math/Rect2.hpp>
#include <libng_core/libcxx/string_view.hpp>

namespace libng {

class BaseWindow : public NonCopyable {
public:
  struct CreateDesc {
    enum class Type
    {
      None,
      NormalWindow,
      ToolWindow,
      PopupWindow,
    };

    CreateDesc();

    ~CreateDesc();

    Type type = Type::NormalWindow;

    Rect2f rect{13, 17, 800, 768}; // Issue: Hard Coding

    bool titleBar : 1;
    bool isMainWindow : 1;
    bool visible : 1;
    bool resizable : 1;
    bool closeButton : 1;
    bool minButton : 1;
    bool maxButton : 1;
    bool centerToScreen : 1;
    bool alwaysOnTop : 1;
  };

  BaseWindow();

  ~BaseWindow();

  void create(CreateDesc& desc);

  void setWindowTitle(StrView title);

  void drawNeeded();

  const Rect2f& clientRect() const;

  virtual void onCloseButton();

  virtual void onActive(bool isActive);

  virtual void onDraw();

protected:
  virtual void onCreate(CreateDesc& desc);

  virtual void onSetWindowTitle(StrView title);

  virtual void onClientRectChanged(const Rect2f& rc);

  virtual void onDrawNeeded();

  Rect2f _clientRect{0, 0, 0, 0};
};

} // namespace libng
