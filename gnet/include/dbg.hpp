#pragma once

#ifdef _MSC_VER
#define __GNET_PRETTY_FUNCTION__ (__FUNCSIG__)
#else
#define __GNET_PRETTY_FUNCTION__ (__PRETTY_FUNCTION__)
#endif
