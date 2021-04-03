#include <memory>

#include "client/game.hpp"
#include "client/imgui/ui.hpp"

#include "pch.hpp"

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

bool gnet::game::get_input_key(SDL_Keycode key) {
  auto idx = SDL_GetScancodeFromKey(key);
  return ImGui::GetIO().KeysDown[idx];
}
