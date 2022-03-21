#pragma once

#ifdef _MSC_VER
#define __LIBNG_PRETTY_FUNCTION__ (__FUNCSIG__)
#else
#define __LIBNG_PRETTY_FUNCTION__ (__PRETTY_FUNCTION__)
#endif
