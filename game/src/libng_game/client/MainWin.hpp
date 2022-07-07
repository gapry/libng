#pragma once

namespace libng {

class MainWin : public UIWindow {
  using Base = UIWindow;

public:
  void onCreate(CreateDesc& desc);

  virtual void onCloseButton() override {
    UIApp::current()->quit(0);
  }

  virtual void onDraw();

  SPtr<RenderContext> _renderContext;
  RenderCommandBuffer _cmdBuf;
  RenderMesh _renderMesh;
};

} // namespace libng
