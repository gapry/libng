#pragma once

#include <platform/os.hpp>

#if LIBNG_OS_WINDOWS
#define LIBNG_RENDER_DX11   1
#define LIBNG_RENDER_OpenGL 1
#endif

#if LIBNG_OS_Linux
#define LIBNG_RENDER_OpenGL 1
#endif