#pragma once

#include <platform/os.hpp>

#ifdef _MSC_VER
#define __LIBNG_PRETTY_FUNCTION__ (__FUNCSIG__)
#else
#define __LIBNG_PRETTY_FUNCTION__ (__PRETTY_FUNCTION__)
#endif

#ifdef LIBNG_OS_WINDOWS
#define LIBNG_INLINE __forceinline
#else
#define LIBNG_INLINE inline
#endif