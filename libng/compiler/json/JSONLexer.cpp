#include <compiler/json/JSONLexer.hpp>

#include <log/log.hpp>
#include <types/function.hpp>

namespace libng {

void JSONLexer::nextChar() {
  LIBNG_LOG("{}\n", __LIBNG_PRETTY_FUNCTION__);
}

} // namespace libng