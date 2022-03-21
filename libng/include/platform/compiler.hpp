#pragma once

#include "platform/os.hpp"

#ifdef LIBNG_OS_WINDOWS
#define LIBNG_INLINE __forceinline
#else
#define LIBNG_INLINE inline
#endif
