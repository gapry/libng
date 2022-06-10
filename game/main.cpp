#include <log/log.hpp>
#include <log/variable.hpp>
#include <types/function.hpp>
#include <exception/error.hpp>
#include <memory/SPtr.hpp>
#include <file/FilePath.hpp>

#include <ui/UIApp.hpp>
#include <ui/UIWindow.hpp>

#include <libcxx/util/util.hpp>

#include <platform/graphics.hpp>

#include <renderer/Renderer.hpp>
#include <renderer/RenderContext.hpp>
#include <renderer/mesh/RenderMesh.hpp>
#include <renderer/vertex/VertexCommon.hpp>
#include <renderer/buffer/RenderCommandBuffer.hpp>
#include <renderer/mesh/WavefrontObjLoader.hpp>

namespace libng {

class MainWin : public UIWindow {
  using Base = UIWindow;

public:
  void onCreate(CreateDesc& desc) {
    LIBNG_DUMP_VAR(sizeof(VertexPos3f));
    LIBNG_DUMP_VAR(sizeof(VertexPos3fColor4b));

    Base::onCreate(desc);

    auto* renderer = Renderer::current();

    {
      RenderContext::CreateDesc renderContextDesc;
      renderContextDesc.window = this;
      _renderContext           = renderer->createContext(renderContextDesc);
    }

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

    VertexLayoutManager::current()->getLayout(VertexPos3f::kType);
  }

  virtual void onCloseButton() override {
    UIApp::current()->quit(0);
  }

  virtual void onDraw() {
    Base::onDraw();
    if (!_renderContext)
      return;

    _renderContext->setFrameBufferSize(clientRect().size);

    _renderContext->beginRender();

    _cmdBuf.reset();
    _cmdBuf.clearFrameBuffer()->setColor({0, 0, 0.2f, 1});
    _cmdBuf.drawMesh(LIBNG_SRC_LOC, _renderMesh);
    _cmdBuf.swapBuffers();

    _renderContext->commit(_cmdBuf);

    _renderContext->endRender();
    drawNeeded();
  }

  SPtr<RenderContext> _renderContext;
  RenderCommandBuffer _cmdBuf;
  RenderMesh _renderMesh;
};

class GameApp : public UIApp {
  using Base = UIApp;

public:
  virtual void onCreate(CreateDesc& desc) override {
    {
      String file = getExecutableFilename();
      String path = FilePath::getDir(file);

      String configPath;
#if 1
      configPath = "/../../Assets";
#else
      configPath = "/../../../../Assets";
#endif
      path.append(configPath);
      setCurrentDir(path);

      auto dir = getCurrentDir();
      LIBNG_LOG("Current Dir = {}\n", dir);
    }

    Base::onCreate(desc);
    Renderer::CreateDesc renderDesc;
    Renderer::create(renderDesc);

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
