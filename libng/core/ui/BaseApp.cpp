#include <ui/BaseApp.hpp>

namespace libng {

int BaseApp::run(CreateDesc& desc) {
  onCreate(desc);
  onRun();
  return _exitCode;
}

void BaseApp::quit(int exitCode) {
  _exitCode = exitCode;
  onQuit();
}

void BaseApp::willQuit() {
}

void BaseApp::onCreate(CreateDesc& desc) {
}

void BaseApp::onRun() {
}

void BaseApp::onQuit() {
}

} // namespace libng