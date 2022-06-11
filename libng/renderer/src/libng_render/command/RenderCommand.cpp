#include <libng_render/command/RenderCommand.hpp>

namespace libng {

RenderCommand::RenderCommand(Type type)
  : _type(type) {
}

/**
 * @brief public member method
 *
 * @return RenderCommand::Type
 */
RenderCommand::Type RenderCommand::getType() const {
  return _type;
}

} // namespace libng