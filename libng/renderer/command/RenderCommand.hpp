#pragma once

#include <types/noncopyable.hpp>

#include <debug/SourceLocation.hpp>
#include <debug/Util.hpp>

#include <renderer/command/RenderCommandType.hpp>

namespace libng {

class RenderCommand : NonCopyable {
public:
  using Type = RenderCommandType;

  RenderCommand(Type type);

  virtual ~RenderCommand() = 0;

  Type getType() const;

#if LIBNG_DEBUG
  SrcLoc debugLoc;
#endif

private:
  Type _type = Type::None;
};

} // namespace libng