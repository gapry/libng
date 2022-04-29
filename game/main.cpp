#include <log/log.hpp>
#include <log/variable.hpp>
#include <types/function.hpp>
#include <exception/error.hpp>
#include <ui/UIApp.hpp>
#include <ui/UIWindow.hpp>
#include <third_party/eastl/eastl.hpp>

namespace libng {

class MainWin : public UIWindow {
  using Base = UIWindow;

public:
  void onCreate(CreateDesc& desc) {
    Base::onCreate(desc);
  }

  virtual void onCloseButton() override {
    UIApp::current()->quit(0);
  }

  virtual void onDraw() {
    Base::onDraw();
    drawNeeded();
  }
};

class GameApp : public UIApp {
  using Base = UIApp;

public:
  virtual void onCreate(CreateDesc& desc) override {
    Base::onCreate(desc);

    UIWindow::CreateDesc winDesc;
    winDesc.isMainWindow = true;
    _mainWin.create(winDesc);
  }

private:
  MainWin _mainWin;
};

} // namespace libng

int main() {
  libng::GameApp app;
  libng::GameApp::CreateDesc desc;
  app.run(desc);
  return 0;
}
