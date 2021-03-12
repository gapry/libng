#include "client/ui.h"

void gnet::ui::init_imgui(ImGuiIO& io) {
  IMGUI_CHECKVERSION();

  ImGui::CreateContext();

  io = ImGui::GetIO();

  (void)io;

  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

  ImGui::StyleColorsDark();
}

int gnet::ui::init_opengl_loader(void) {
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
    return 1;
  }
  return 0;
}

int gnet::ui::init_sdl(void) {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0) {
    fmt::print("Error: {}\n", SDL_GetError());
    return -1;
  }
  return 0;
}

gnet::ui::ui(ImGuiIO& io,                                               //
             SDL_Window* window,                                        //
             gnet::player& player,                                      //
             void (*game_loop)(SDL_Window*, ImGuiIO&, gnet::player&)) { //
  init_sdl();

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

  init_opengl_loader();

  init_imgui(io);

  ImGui_ImplSDL2_InitForOpenGL(window, gl_context);

  ImGui_ImplOpenGL3_Init(glsl_version);

  game_loop(window, io, player);
}

gnet::ui::~ui() {
  ImGui_ImplOpenGL3_Shutdown();

  ImGui_ImplSDL2_Shutdown();

  ImGui::DestroyContext();

  SDL_GL_DeleteContext(gl_context);

  SDL_DestroyWindow(window);

  SDL_Quit();
}
