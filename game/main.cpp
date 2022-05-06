#include <log/log.hpp>
#include <log/variable.hpp>
#include <types/function.hpp>
#include <exception/error.hpp>

#include <ui/UIApp.hpp>
#include <ui/UIWindow.hpp>

#include <libcxx/util.hpp>

#include <platform/graphics.hpp>
#include <renderer/Renderer.hpp>
#include <renderer/vertex/VertexCommon.hpp>

namespace libng {

class MainWin : public UIWindow {
  using Base = UIWindow;

public:
  void onCreate(CreateDesc& desc) {
    LIBNG_DUMP_VAR(sizeof(VertexPos3f));
    LIBNG_DUMP_VAR(sizeof(VertexPos3fColor4b));

    Base::onCreate(desc);

    auto* renderer = Renderer::current();
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
