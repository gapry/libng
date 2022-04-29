#include <renderer/command/RenderCommandType.hpp>
#include <types/noncopyable.hpp>

namespace libng {

class RenderCommand : NonCopyable {
public:
  using Type = RenderCommandType;

  RenderCommand(Type type);

  virtual ~RenderCommand();

private:
  Type _type = Type::None;
};

} // namespace libng