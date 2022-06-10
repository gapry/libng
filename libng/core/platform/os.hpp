#pragma once

#if _WIN64
#define LIBNG_OS_WIN64 1
#elif _WIN32
#define LIBNG_OS_WIN32 1
#endif

#if LIBNG_OS_WIN32 + LIBNG_OS_WIN64
#define LIBNG_OS_WINDOWS 1
#endif

#if LIBNG_OS_WINDOWS
#define NOMINMAX 1
#include <WinSock2.h>              // WinSock2.h must include before windows.h to avoid winsock1 define
#include <ws2tcpip.h>              // struct sockaddr_in6
#pragma comment(lib, "Ws2_32.lib") //
#include <Windows.h>               //
#include <Windowsx.h>              //
#include <intsafe.h>               //
#endif

#if __APPLE__ && __MACH__
#define LIBNG_OS_MACOS 1
#endif

#if __linux
#define LIBNG_OS_LINUX 1
#endif

#if __FreeBSD__
#define LIBNG_OS_FREEBSD 1
#endif

#if LIBNG_OS_WINDOWS + LIBNG_OS_MACOS + LIBNG_OS_LINUX + LIBNG_OS_FREEBSD != 1
#define LIBNG_OS_UNSUPPORTED 1
#error "[ERROR] libng cloud not detect the OS."
#endif
