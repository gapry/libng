#pragma once

#include <cassert>
#include <exception>

#include <libcxx/fmt.hpp>
#include <types/function.hpp>
#include <third_party/eastl/eastl.hpp>

#define LIBNG_ASSERT(...) assert(__VA_ARGS__)

#define LIBNG_SRC_LOC     libng::SrcLoc(__FILE__, __LINE__, __LIBNG_PRETTY_FUNCTION__)

#define LIBNG_ERROR(...)  libng::Error(LIBNG_SRC_LOC, libng::Fmt(__VA_ARGS__))

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
  const char* func;
  int line = 0;
};

class IError : public std::exception {
public:
};

class Error : public IError {
public:
  Error(const SrcLoc& loc, StrView msg);

private:
  SrcLoc _loc;
  TempString _msg;
};

} // namespace libng