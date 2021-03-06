#pragma once

#include <libng_game/libng_game_common.hpp>

namespace libng {

class MainWin : public UIWindow {
  using Base = UIWindow;

public:
  void onCreate(CreateDesc& desc);

  virtual void onCloseButton() override;
  virtual void onDraw();
  virtual void onUIMouseEvent(UIMouseEvent& ev) override;

  // clang-format off
  Renderer*           _renderer = nullptr;
  SPtr<Material>      _material;
  SPtr<Texture2D>     _texture;
  SPtr<RenderContext> _renderContext;
  RenderCommandBuffer _cmdBuf;
  RenderMesh          _renderMesh;
  math::Camera3f      _camera;
  // clang-format on

private:
  void _InitRenderer();
  void _InitTexture();
  void _InitMaterial();
  void _InitMesh();

  void _RenderStatistic();
};

} // namespace libng
