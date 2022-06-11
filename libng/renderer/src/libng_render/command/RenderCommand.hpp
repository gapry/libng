#pragma once

#include <libng_core/types/noncopyable.hpp>
#include <libng_core/debug/SourceLocation.hpp>
#include <libng_core/debug/Util.hpp>
#include <libng_render/command/RenderCommandType.hpp>

namespace libng {

class RenderCommand : NonCopyable {
public:
  using Type = RenderCommandType;

  RenderCommand(Type type);

  virtual ~RenderCommand() {
  }

  Type getType() const;

#if LIBNG_DEBUG
  SrcLoc debugLoc;
#endif

private:
  Type _type = Type::None;
};

} // namespace libng