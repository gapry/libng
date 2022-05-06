#pragma once

#include <platform/os.hpp>

#if LIBNG_OS_WINDOWS
#define LIBNG_RENDER_DX11   1
#define LIBNG_RENDER_OpenGL 1
#endif

#if LIBNG_RENDER_DX11

#include <Windows.h>
#include <Windowsx.h>

#include <d3d11.h>
#include <d3d11_4.h>
#include <dxgi1_4.h>

#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#endif

#if LIBNG_OS_Linux
#define LIBNG_RENDER_OpenGL 1
#endif