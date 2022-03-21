#include <memory>

#include "client/game.hpp"

libng::game::game(void) {
}

libng::game::~game(void) {
}

void libng::game::execute(void) {
  auto game = std::make_unique<libng::ui>(this);
  game->execute();
}

void libng::game::on_update(float delta_time) {
}

void libng::game::on_event(SDL_Event& event) {
}

bool libng::game::get_input_key(SDL_Keycode key) {
  auto idx = SDL_GetScancodeFromKey(key);
  return ImGui::GetIO().KeysDown[idx];
}
