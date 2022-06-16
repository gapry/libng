#pragma once

#include <libng_core/platform/os.hpp>

#ifdef _MSC_VER
#define __LIBNG_FUNC__ (__func__)
#else
#define __LIBNG_FUNC__ (__FUNC__)
#endif

#ifdef _MSC_VER
#define __LIBNG_FUNCTION__ (__FUNCTION__)
#else
#define __LIBNG_FUNCTION__ (__FUNCTION__)
#endif

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

#define LIBNG_GET_FUNCTION_NAME(sig) #sig