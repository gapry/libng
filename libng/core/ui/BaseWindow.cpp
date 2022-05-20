#include <ui/BaseWindow.hpp>

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

const Rect2f& BaseWindow::clientRect() const {
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

void BaseWindow::onClientRectChanged(const Rect2f& rc) {
  _clientRect = rc;
}

void BaseWindow::onDrawNeeded() {
}

} // namespace libng