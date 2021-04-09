#include "ui/imgui/imgui.hpp"

void gnet::ui::on_update(void) {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    ImGui_ImplSDL2_ProcessEvent(&event);
    if (event.type == SDL_QUIT) {
      m_is_executed = false;
    }
    if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE &&
        event.window.windowID == SDL_GetWindowID(window)) {
      m_is_executed = false;
    }
    m_owner->on_event(event);
  }

  ImGui_ImplOpenGL3_NewFrame();

  ImGui_ImplSDL2_NewFrame(window);

  ImGui::NewFrame();

  m_owner->on_update(ImGui::GetIO().DeltaTime);
}

void gnet::ui::on_render(void) {
  ImGui::Render();

  ImGuiIO& io = ImGui::GetIO();

  glViewport(0,                      //
             0,                      //
             (int)io.DisplaySize.x,  //
             (int)io.DisplaySize.y); //

  glClearColor(clear_color.x * clear_color.w, //
               clear_color.y * clear_color.w, //
               clear_color.z * clear_color.w, //
               clear_color.w);                //

  glClear(GL_COLOR_BUFFER_BIT);

  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  SDL_GL_SwapWindow(window);
}

void gnet::ui::execute(void) {
  while (m_is_executed) {
    on_update();
    on_render();
  }
}

gnet::ui::ui(gnet::game* owner)
  : m_owner(owner) {
  int error = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER);
  if (error != 0) {
    fmt::print("Error: {}\n", SDL_GetError());
  }

#ifdef __APPLE__
  // GL 3.2 Core + GLSL 150
  glsl_version = (char*)"#version 150";
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS,                    //
                      SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); //
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#else
  // GL 3.0 + GLSL 130
  glsl_version = (char*)"#version 130";
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,  //
                      SDL_GL_CONTEXT_PROFILE_CORE); //
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#endif

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

  SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL |        //
                                                   SDL_WINDOW_RESIZABLE |     //
                                                   SDL_WINDOW_ALLOW_HIGHDPI); //

  window = SDL_CreateWindow("GNet Client",          //
                            SDL_WINDOWPOS_CENTERED, //
                            SDL_WINDOWPOS_CENTERED, //
                            800,                    //
                            600,                    //
                            window_flags);          //

  SDL_GLContext gl_context = SDL_GL_CreateContext(window);

  SDL_GL_MakeCurrent(window, gl_context);

  SDL_GL_SetSwapInterval(1);

#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
  bool err = gl3wInit() != 0;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
  bool err = glewInit() != GLEW_OK;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
  bool err = gladLoadGL() == 0;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD2)
  bool err = gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress) == 0;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING2)
  bool err = false;
  glbinding::Binding::initialize();
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING3)
  bool err = false;
  glbinding::initialize([](const char* name) {
    return (glbinding::ProcAddress)SDL_GL_GetProcAddress(name); //
  });
#else
  bool err = false;
#endif
  if (err) {
    fprintf(stderr, "Failed to initialize OpenGL loader!\n");
  }

  IMGUI_CHECKVERSION();

  ImGui::CreateContext();

  ImGui::StyleColorsDark();

  ImGui_ImplSDL2_InitForOpenGL(window, gl_context);

  ImGui_ImplOpenGL3_Init(glsl_version);
}

gnet::ui::~ui() {
  ImGui_ImplOpenGL3_Shutdown();

  ImGui_ImplSDL2_Shutdown();

  ImGui::DestroyContext();

  SDL_GL_DeleteContext(gl_context);

  SDL_DestroyWindow(window);

  SDL_Quit();
}
