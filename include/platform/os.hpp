#pragma once

#if _WIN64
#define GNET_OS_WIN64 1
#elif _WIN32
#define GNET_OS_WIN32 1
#endif

#if GNET_OS_WIN32 + GNET_OS_WIN64
#define GNET_OS_WINDOWS 1
#endif

#if __linux
#define GNET_OS_LINUX 1
#endif

#if __FreeBSD__
#define GNET_OS_FREEBSD 1
#endif

#if GNET_OS_WINDOWS + GNET_OS_LINUX + GNET_OS_FREEBSD != 1
#error "[ERROR] GNet cloud not detect the OS."
#endif
