#include "app_client.hpp"

// void libng::app_client::on_update(float delta_time) {
//   auto* drawList = ImGui::GetBackgroundDrawList();
//
//   player.set_x(player.get_x() + get_dir_x() * get_speed() * delta_time);
//   player.set_y(player.get_x() + get_dir_y() * get_speed() * delta_time);
//
//   auto px = player.get_x();
//   auto py = player.get_y();
//
//   auto delta = 10;
//   drawList->AddTriangleFilled(ImVec2(px, py - delta),         //
//                               ImVec2(px - delta, py + delta), //
//                               ImVec2(px + delta, py + delta), //
//                               ImColor(123, 231, 312));        //
// }
//
// void libng::app_client::on_event(SDL_Event& event) {
//   switch (event.type) {
//     case SDL_KEYDOWN: {
//       auto key = event.key.keysym.sym;
//       switch (key) {
//         case SDLK_w: {
//         } break;
//         case SDLK_a: {
//         } break;
//         case SDLK_s: {
//         } break;
//         case SDLK_d: {
//         } break;
//       }
//     } break;
//   }
// }
//