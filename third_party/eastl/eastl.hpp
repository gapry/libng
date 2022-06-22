#pragma once

#include <EASTL/fixed_string.h>
#include <EASTL/fixed_vector.h>
#include <EASTL/span.h>
#include <EASTL/string.h>
#include <EASTL/string_view.h>
#include <EASTL/vector.h>

#include <EASTL/optional.h>

#include <EASTL/hash_map.h>
#include <EASTL/map.h>
#include <EASTL/string_map.h>
#include <EASTL/vector_map.h>

#include <EASTL/shared_ptr.h>
#include <EASTL/unique_ptr.h>
#include <EASTL/weak_ptr.h>

#include <libng_core/types/function.hpp>

#if !EASTL_DLL

#pragma warning(push)
#pragma warning(disable : 4100)

LIBNG_INLINE auto operator new[](size_t size,          //
                                 char const* p_name,   //
                                 int flags,            //
                                 unsigned debug_flags, //
                                 char const* file,     //
                                 int line) -> void* {  //
  return malloc(size);
}

LIBNG_INLINE auto operator new[](size_t size,             //
                                 size_t alignment,        //
                                 size_t alignment_offset, //
                                 char const* p_name,      //
                                 int flags,               //
                                 unsigned debug_flags,    //
                                 char const* file,        //
                                 int line) -> void* {     //
#if LIBNG_OS_WINDOWS
  return _aligned_malloc(size, alignment);
#else
  return std::aligned_alloc(alignment, size);
#endif
}

#pragma warning(pop)

#endif