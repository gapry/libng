#pragma once

#ifdef _WIN32
#define GNET_INLINE __forceinline
#else
#define GNET_INLINE inline
#endif
