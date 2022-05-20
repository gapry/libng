#pragma once

#include <cassert>
#include <exception>

#include <libcxx/fmt.hpp>
#include <libcxx/util.hpp>

#include <types/function.hpp>
#include <debug/SourceLocation.hpp>

#define LIBNG_ASSERT(...) assert(__VA_ARGS__)

#define LIBNG_SRC_LOC     libng::SrcLoc(__FILE__, __LINE__, __LIBNG_PRETTY_FUNCTION__)

#define LIBNG_ERROR(...)  libng::Error(LIBNG_SRC_LOC, libng::Fmt(__VA_ARGS__))

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