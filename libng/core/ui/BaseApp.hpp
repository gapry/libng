#pragma once

#include <types/noncopyable.hpp>
#include <libcxx/util/util.hpp>

namespace libng {

class BaseApp : public NonCopyable {
public:
  class CreateDesc {
  public:
  };

  int run(CreateDesc& desc);

  void quit(int returnCode);

  virtual void willQuit();

  void setCurrentDir(StrView dir) {
    onSetCurrentDir(dir);
  }

  String getCurrentDir() {
    return onGetCurrentDir();
  }

  String getExecutableFilename() {
    return onGetExecutableFilename();
  }

protected:
  virtual String onGetExecutableFilename() = 0;

  virtual String onGetCurrentDir() = 0;

  virtual void onSetCurrentDir(StrView dir) = 0;

  virtual void onCreate(CreateDesc& desc);

  virtual void onRun();

  virtual void onQuit();

  int _exitCode = 0;
};

} // namespace libng
