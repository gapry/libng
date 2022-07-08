#pragma once

namespace libng {

class MainWin : public UIWindow {
  using Base = UIWindow;

public:
  void onCreate(CreateDesc& desc);

  virtual void onCloseButton() override;
  virtual void onDraw();

  // clang-format off
  Renderer*           _renderer = nullptr;
  SPtr<Material>      _material;
  SPtr<Texture2D>     _texture;
  SPtr<RenderContext> _renderContext;
  RenderCommandBuffer _cmdBuf;
  RenderMesh          _renderMesh;
  // clang-format on

private:
  void _InitRenderer();
  void _InitTexture();
  void _InitMaterial();
  void _InitMesh();

  void _RenderStatistic();
};

} // namespace libng
