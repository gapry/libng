#pragma once

#include "platform/os.hpp"

#ifdef GNET_OS_WINDOWS
#define GNET_INLINE __forceinline
#else
#define GNET_INLINE inline
#endif
