#include <libng_game/client/MainWin.hpp>

namespace libng {

void MainWin::onCreate(CreateDesc& desc) {
  _RenderStatistic();

  Base::onCreate(desc);

  _InitRenderer();
  _InitTexture();
  _InitMaterial();
  _InitMesh();

  VertexLayoutManager::current()->getLayout(VertexPos3f::kType);
}

void MainWin::onDraw() {
  Base::onDraw();
  if (!_renderContext) {
    return;
  }

  _renderContext->setFrameBufferSize(clientRect().size);
  _renderContext->beginRender();
  {
    _cmdBuf.reset();
    _cmdBuf.clearFrameBuffer()->setColor({0, 0, 0.2f, 1});
    _cmdBuf.drawMesh(LIBNG_SRC_LOC, _renderMesh);
    _cmdBuf.swapBuffers();

    _renderContext->commit(_cmdBuf);
  }
  _renderContext->endRender();

  drawNeeded();
}

void MainWin::onCloseButton() {
  UIApp::current()->quit(0);
}

void MainWin::_InitRenderer() {
  _renderer = Renderer::instance();
  {
    RenderContext::CreateDesc renderContextDesc;
    renderContextDesc.window = this;
    _renderContext           = _renderer->createContext(renderContextDesc);
  }
}

void MainWin::_InitTexture() {
  Texture2D_CreateDesc texDesc;

  auto& image = texDesc.imageToUpload;
#if 0
  image.loadFile("Assets/Textures/uvChecker/uvChecker.png");
  // image.loadFile("Assets/Textures/uvChecker/uvChecker_BC1.dds");
  // image.loadFile("Assets/Textures/uvChecker/uvChecker_BC2.dds");
  // image.loadFile("Assets/Textures/uvChecker/uvChecker_BC3.dds");
  // image.loadFile("Assets/Textures/uvChecker/uvChecker_BC7.dds");

  texDesc.size      = image.size();
  texDesc.colorType = image.colorType();
#else
  int w = 256;
  int h = 256;

  texDesc.size.set(w, h);
  texDesc.colorType = math::ColorType::RGBAb;

  image.create(math::Color4b::kColorType, w, h);

  for (int y = 0; y < w; y++) {
    auto span = image.row<math::Color4b>(y);
    for (int x = 0; x < h; x++) {
      span[x] = math::Color4b(static_cast<u8>(x), static_cast<u8>(y), 0, 255);
    }
  }
#endif

  _texture = _renderer->createTexture2D(texDesc);
}

void MainWin::_InitMaterial() {
  _material = _renderer->createMaterial();
}

void MainWin::_InitMesh() {
  EditMesh editMesh;

#if 1
  WavefrontObjLoader::loadFile(editMesh, "Mesh/test.obj"); // Issue
  // the current shader need color
  for (size_t i = editMesh.color.size(); i < editMesh.pos.size(); i++) {
    editMesh.color.emplace_back(255, 255, 255, 255);
  }

  // the current shader has no uv or normal
  editMesh.uv[0].clear();
  editMesh.normal.clear();

#else
  editMesh.pos.emplace_back(0.0f, 0.5f, 0.0f);
  editMesh.pos.emplace_back(0.5f, -0.5f, 0.0f);
  editMesh.pos.emplace_back(-0.5f, -0.5f, 0.0f);
  editMesh.color.emplace_back(255, 0, 0, 255);
  editMesh.color.emplace_back(0, 255, 0, 255);
  editMesh.color.emplace_back(0, 0, 255, 255);
#endif

  _renderMesh.create(editMesh);
}

void MainWin::_RenderStatistic() {
  LIBNG_DUMP_VAR(sizeof(VertexPos3f));
  LIBNG_DUMP_VAR(sizeof(VertexPos3fColor4b));
}

} // namespace libng