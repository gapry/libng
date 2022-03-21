#pragma once

#if _WIN64
#define LIBNG_OS_WIN64 1
#elif _WIN32
#define LIBNG_OS_WIN32 1
#endif

#if LIBNG_OS_WIN32 + LIBNG_OS_WIN64
#define LIBNG_OS_WINDOWS 1
#endif

#if __linux
#define LIBNG_OS_LINUX 1
#endif

#if __FreeBSD__
#define LIBNG_OS_FREEBSD 1
#endif

#if LIBNG_OS_WINDOWS + LIBNG_OS_LINUX + LIBNG_OS_FREEBSD != 1
#error "[ERROR] libng cloud not detect the OS."
#endif
