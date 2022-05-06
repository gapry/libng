#pragma once

#include <types/number.hpp>

#include <renderer/vertex/VertexType.hpp>
#include <renderer/vertex/VertexTypeUtil.hpp>
#include <renderer/type/RenderDataType.hpp>

namespace libng {

// total         : 64 bit
// ----------------------
// posType			 :  8 bit
// colorType		 :  8 bit
// colorCount		 :  2 bit
// uvType			   :  8 bit
// uvCount			 :  8 bit
// normalType		 :  8 bit
// normalCount	 :  2 bit
// tangentCount	 :  2 bit
// binormalCount :  2 bit
struct VertexTypeUtil {
  // ---------------------------------------------------------------------------------------------
  // vertexType : xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx
  // posType    : 0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_????_????
  // ---------------------------------------------------------------------------------------------
  static constexpr VertexType addPos(VertexType vertexType, RenderDataType posType) {
    return static_cast<VertexType>(static_cast<u64>(vertexType) | //
                                   static_cast<u64>(posType));
  }

  // ---------------------------------------------------------------------------------------------
  // vertexType : xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx
  // posType    : 0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_????_????
  // colorType  : 0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_????_????_0000_0000
  // colorCount : 0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_00??_0000_0000_0000_0000
  // ---------------------------------------------------------------------------------------------
  static constexpr VertexType addColor(VertexType vertexType, RenderDataType colorType, u8 colorCount) {
    return static_cast<VertexType>(static_cast<u64>(vertexType) |         //
                                   (static_cast<u64>(colorType) << 8) |   //
                                   (static_cast<u64>(colorCount) << 16)); //
  }

  // ---------------------------------------------------------------------------------------------
  // vertexType : xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx
  // posType    : 0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_????_????
  // colorType  : 0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_????_????_0000_0000
  // colorCount : 0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_00??_0000_0000_0000_0000
  // uvType     : 0000_0000_0000_0000_0000_0000_0000_0000_0000_00??_????_??00_0000_0000_0000_0000
  // uvCount    : 0000_0000_0000_0000_0000_0000_0000_00??_????_??00_0000_0000_0000_0000_0000_0000
  // ---------------------------------------------------------------------------------------------
  static constexpr VertexType addUv(VertexType vertexType, RenderDataType uvType, u8 uvCount) {
    return static_cast<VertexType>(static_cast<u64>(vertexType) |      //
                                   (static_cast<u64>(uvType) << 18) |  //
                                   (static_cast<u64>(uvCount) << 26)); //
  }

  // ---------------------------------------------------------------------------------------------
  // vertexType  : xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx
  // posType     : 0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_????_????
  // colorType   : 0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_????_????_0000_0000
  // colorCount  : 0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_00??_0000_0000_0000_0000
  // uvType      : 0000_0000_0000_0000_0000_0000_0000_0000_0000_00??_????_??00_0000_0000_0000_0000
  // uvCount     : 0000_0000_0000_0000_0000_0000_0000_00??_????_??00_0000_0000_0000_0000_0000_0000
  // normalType  : 0000_0000_0000_0000_0000_00??_????_??00_0000_0000_0000_0000_0000_0000_0000_0000
  // normalCount : 0000_0000_0000_0000_0000_??00_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000
  // ---------------------------------------------------------------------------------------------
  static constexpr VertexType addNormal(VertexType vertexType, RenderDataType normalType, u8 normalCount) {
    return static_cast<VertexType>(static_cast<u64>(vertexType) |          //
                                   (static_cast<u64>(normalType) << 34) |  //
                                   (static_cast<u64>(normalCount) << 42)); //
  }

  // ---------------------------------------------------------------------------------------------
  // vertexType   : xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx
  // posType      : 0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_????_????
  // colorType    : 0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_????_????_0000_0000
  // colorCount   : 0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_00??_0000_0000_0000_0000
  // uvType       : 0000_0000_0000_0000_0000_0000_0000_0000_0000_00??_????_??00_0000_0000_0000_0000
  // uvCount      : 0000_0000_0000_0000_0000_0000_0000_00??_????_??00_0000_0000_0000_0000_0000_0000
  // normalType   : 0000_0000_0000_0000_0000_00??_????_??00_0000_0000_0000_0000_0000_0000_0000_0000
  // normalCount  : 0000_0000_0000_0000_0000_??00_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000
  // tangentCount : 0000_0000_0000_0000_00??_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000
  // ---------------------------------------------------------------------------------------------
  static constexpr VertexType addTangent(VertexType vertexType, u8 tangentCount) {
    return static_cast<VertexType>(static_cast<u64>(vertexType) |           //
                                   (static_cast<u64>(tangentCount) << 44)); //
  }

  // ---------------------------------------------------------------------------------------------
  // vertexType    : xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx_xxxx
  // posType       : 0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_????_????
  // colorType     : 0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_????_????_0000_0000
  // colorCount    : 0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_00??_0000_0000_0000_0000
  // uvType        : 0000_0000_0000_0000_0000_0000_0000_0000_0000_00??_????_??00_0000_0000_0000_0000
  // uvCount       : 0000_0000_0000_0000_0000_0000_0000_00??_????_??00_0000_0000_0000_0000_0000_0000
  // normalType    : 0000_0000_0000_0000_0000_00??_????_??00_0000_0000_0000_0000_0000_0000_0000_0000
  // normalCount   : 0000_0000_0000_0000_0000_??00_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000
  // tangentCount  : 0000_0000_0000_0000_00??_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000
  // binormalCount : 0000_0000_0000_0000_??00_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000
  // ---------------------------------------------------------------------------------------------
  static constexpr VertexType addBinormal(VertexType vertexType, u8 binormalCount) {
    return static_cast<VertexType>(static_cast<u64>(vertexType) |            //
                                   (static_cast<u64>(binormalCount) << 46)); //
  }

  static constexpr VertexType make(RenderDataType posType,
                                   RenderDataType colorType,
                                   u8 colorCount,
                                   RenderDataType uvType,
                                   u8 uvCount,
                                   RenderDataType normalType,
                                   u8 normalCount,
                                   u8 tangentCount,
                                   u8 binormalCount) {
    VertexType vertexType = addPos(VertexType::None, posType); // require, mesh must exists position

    if (colorCount) {
      vertexType = addColor(vertexType, colorType, colorCount);
    }

    if (uvCount) {
      vertexType = addUv(vertexType, uvType, uvCount);
    }

    if (normalCount) {
      vertexType = addNormal(vertexType, normalType, normalCount);
      vertexType = addTangent(vertexType, tangentCount);
      vertexType = addBinormal(vertexType, binormalCount);
    }

    return vertexType;
  }
};

} // namespace libng