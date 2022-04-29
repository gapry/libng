#include <renderer/command/RenderCommand.hpp>

namespace libng {

RenderCommand::RenderCommand(Type type)
  : _type(type) {
}

RenderCommand::~RenderCommand() {
}

} // namespace libng