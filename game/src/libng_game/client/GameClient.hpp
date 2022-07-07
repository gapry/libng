#pragma once

#include <libng_game/client/MainWin.hpp>

namespace libng {

class GameClient : public UIApp {
  using Base = UIApp;

public:
  virtual void onCreate(CreateDesc& desc) override;

private:
  MainWin _mainWin;
};

} // namespace libng