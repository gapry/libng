#pragma once

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"

#include <SDL.h>

#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)         //
#include <GL/gl3w.h>                               // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)       //
#include <GL/glew.h>                               // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)       //
#include <glad/glad.h>                             // Initialize with gladLoadGL()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD2)      //
#include <glad/gl.h>                               // Initialize with gladLoadGL(...) or gladLoaderLoadGL()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING2) //
#define GLFW_INCLUDE_NONE                          // GLFW including OpenGL headers causes ambiguity or
                                                   // multiple definition errors.
#include <glbinding/Binding.h>                     // Initialize with glbinding::Binding::initialize()
#include <glbinding/gl/gl.h>                       //
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING3) //
#define GLFW_INCLUDE_NONE                          // GLFW including OpenGL headers causes ambiguity or
                                                   // multiple definition errors.
#include <glbinding/gl/gl.h>                       //
#include <glbinding/glbinding.h>                   // Initialize with glbinding::initialize()
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif
