#pragma once

namespace libng {

class SrcLoc {
public:
  SrcLoc() = default;

  SrcLoc(const char* file_, int line_, const char* func_)
    : file(file_)
    , line(line_)
    , func(func_) {
  }

  ~SrcLoc() = default;

  const char* file = "";
  const char* func = "";
  int line         = 0;
};

} // namespace libng