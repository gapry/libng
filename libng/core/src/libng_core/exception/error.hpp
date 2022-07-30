#pragma once

#include <libng_core/debug/SourceLocation.hpp>
#include <libng_core/libcxx/fmt.hpp>
#include <libng_core/libcxx/string_view.hpp>
#include <libng_core/types/function.hpp>

#define LIBNG_ASSERT(...) assert(__VA_ARGS__)

#define LIBNG_SRC_LOC     libng::SrcLoc(__FILE__, __LINE__, __LIBNG_PRETTY_FUNCTION__)

#define LIBNG_ERROR(...)  libng::Error(LIBNG_SRC_LOC, Fmt(__VA_ARGS__))

namespace libng {

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
