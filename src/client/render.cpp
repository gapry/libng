#include "client/render.h"

void gnet::render::game_loop(SDL_Window* window,     //
                             ImGuiIO& io,            //
                             gnet::player& player) { //
  bool done          = false;
  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
  SDL_Event event;

  while (!done) {
    while (SDL_PollEvent(&event)) {
      ImGui_ImplSDL2_ProcessEvent(&event);
      if (event.type == SDL_QUIT) {
        done = true;
      }
      if (event.type == SDL_WINDOWEVENT &&                    //
          event.window.event == SDL_WINDOWEVENT_CLOSE &&      //
          event.window.windowID == SDL_GetWindowID(window)) { //
        done = true;
      }
      if (event.type == SDL_KEYDOWN) {
        player.movement(event);
      }
    }

    ImGui_ImplOpenGL3_NewFrame();

    ImGui_ImplSDL2_NewFrame(window);

    ImGui::NewFrame();

    ImGui::Render();

    glViewport(0,                      //
               0,                      //
               (int)io.DisplaySize.x,  //
               (int)io.DisplaySize.y); //

    glClearColor(clear_color.x * clear_color.w, //
                 clear_color.y * clear_color.w, //
                 clear_color.z * clear_color.w, //
                 clear_color.w);                //

    glClear(GL_COLOR_BUFFER_BIT);

    player.render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    SDL_GL_SwapWindow(window);
  }
}
