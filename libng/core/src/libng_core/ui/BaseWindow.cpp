#include <libng_core/ui/BaseWindow.hpp>

namespace libng {

BaseWindow::CreateDesc::CreateDesc()
  : titleBar(true)
  , isMainWindow(false)
  , visible(true)
  , resizable(true)
  , closeButton(true)
  , minButton(true)
  , maxButton(true)
  , centerToScreen(true)
  , alwaysOnTop(false) {
}

BaseWindow::CreateDesc::~CreateDesc() {
}

BaseWindow::BaseWindow() {
}

BaseWindow::~BaseWindow() {
}

void BaseWindow::create(CreateDesc& desc) {
  onCreate(desc);
}

void BaseWindow::setWindowTitle(StrView title) {
  onSetWindowTitle(title);
}

void BaseWindow::drawNeeded() {
  onDrawNeeded();
}

const math::Rect2f& BaseWindow::clientRect() const {
  return _clientRect;
}

void BaseWindow::onCloseButton() {
}

void BaseWindow::onActive(bool isActive) {
}

void BaseWindow::onDraw() {
}

void BaseWindow::onCreate(CreateDesc& desc) {
}

void BaseWindow::onSetWindowTitle(StrView title) {
}

void BaseWindow::onClientRectChanged(const math::Rect2f& rc) {
  _clientRect = rc;
}

void BaseWindow::onDrawNeeded() {
}

void BaseWindow::onUINativeMouseEvent(UIMouseEvent& ev) {
  using Button = UIMouseEventButton;
  using Type   = UIMouseEventType;

  // clang-format off
  switch (ev.type) {
    case Type::Down: { BitUtil::set(  _pressedMouseButtons, ev.button); } break;
    case Type::Up:   { BitUtil::unset(_pressedMouseButtons, ev.button); } break;
    default: break;
  }
  // clang-format on
  ev.pressedButtons = _pressedMouseButtons;
  ev.deltaPos       = ev.pos - _mousePos;
  _mousePos         = ev.pos;
  onUIMouseEvent(ev);
}

} // namespace libng