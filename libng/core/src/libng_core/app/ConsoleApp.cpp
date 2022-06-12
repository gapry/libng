#include <libng_core/app/ConsoleApp.hpp>
#include <libng_core/log/log.hpp>

namespace libng {

void ConsoleApp::run(int argc, char** argv) {
  onRun(argc, argv);
}

void ConsoleApp::listArgv(int argc, char** argv) {
  for (int count = 0; count < argc; ++count) {
    LIBNG_LOG("argc = {}, argv = {}", count, argv[count]);
  }
}

} // namespace libng
