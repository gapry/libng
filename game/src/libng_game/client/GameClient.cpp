#include <libng_game/client/GameClient.hpp>

namespace libng {

void GameClient::onCreate(CreateDesc& desc) {
  {
    FilePath::SetAssetsPath("/../../../../Assets/");

    String file       = getExecutableFilename();
    String path       = FilePath::DirName(file);
    String assetsPath = FilePath::GetAssetsPath();
    path.append(assetsPath);
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

} // namespace libng
