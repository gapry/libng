#include <libng_core/log/log.hpp>
#include <libng_core/types/function.hpp>
#include <libng_editor/Button.hpp>

namespace libng {

Button::Button() {
  LIBNG_LOG("{}\n", __LIBNG_PRETTY_FUNCTION__);
}

Button::~Button() {
  LIBNG_LOG("{}\n", __LIBNG_PRETTY_FUNCTION__);
}

} // namespace libng