#include <libng_core/ui/UIApp.hpp>

namespace libng {

UIApp* UIApp::_current;

UIApp* UIApp::current() {
  return _current;
}

UIApp::UIApp() {
  _current = this;
}

} // namespace libng