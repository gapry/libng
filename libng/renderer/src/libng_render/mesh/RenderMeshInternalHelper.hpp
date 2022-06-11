#pragma once

#include <libng_core/types/number.hpp>
#include <libng_core/types/function.hpp>
#include <libng_core/exception/error.hpp>
#include <libng_render/vertex/VertexLayout.hpp>

namespace libng {

struct RenderMeshInternalHelper {
  template<class DST, class T>
  LIBNG_INLINE static void copyVertexData(DST* dst,                             //
                                          size_t vertexCount,                   //
                                          const VertexLayout::Element& element, //
                                          size_t stride,                        //
                                          const T* src) {                       //
    u8* p = dst + element.offset;

    for (size_t i = 0; i < vertexCount; i++) {
      *reinterpret_cast<T*>(p) = *src;
      src++;
      p += stride;
    }
  }

  static bool hasAttr(size_t arraySize, size_t vertexCount) {
    if (arraySize <= 0) {
      return false;
    }

    if (arraySize < vertexCount) {
      LIBNG_ASSERT(false);
      return false;
    }
    return true;
  }
};

} // namespace libng