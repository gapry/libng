#include <libng_core/exception/error.hpp>

namespace libng {

Error::Error(const SrcLoc& loc, StrView msg)
  : _loc(loc)
  , _msg(msg) {
}

} // namespace libng