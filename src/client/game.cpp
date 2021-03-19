#include <memory>

#include "client/game.h"
#include "client/ui.h"

gnet::game::game(void) {
}

gnet::game::~game(void) {
}

void gnet::game::execute(void) {
  auto game = std::make_unique<gnet::ui>(this);
  game->execute();
}

void gnet::game::on_update(float delta_time) {
}

void gnet::game::on_event(SDL_Event& event) {
}
