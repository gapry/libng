#pragma once

#include <libng_core/log/log.hpp>

// clang-format off

#define LIBNG_EMPTY

#define LIBNG_STRINGIFY(...)  #__VA_ARGS__

#define LIBNG_IDENTITY(x) x

#define LIBNG_CALL(M, ARGS) LIBNG_IDENTITY(M(ARGS)) 

#define LIBNG_VA_ARGS_COUNT(...) LIBNG_IDENTITY(LIBNG_VA_ARGS_COUNT_INTERNAL(__VA_ARGS__, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1))

#define LIBNG_VA_ARGS_COUNT_INTERNAL(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, COUNT, ...) COUNT

#define LIBNG_DUMP_VAR_1(v0)              do { LIBNG_LOG("DUMP_VAR: {} = {}\n",                             #v0, (v0)); } while(false)
#define LIBNG_DUMP_VAR_2(v0, v1)          do { LIBNG_LOG("DUMP_VAR: {} = {}, {} = {}\n",                    #v0, (v0), #v1, (v1)); } while(false)
#define LIBNG_DUMP_VAR_3(v0, v1, v2)      do { LIBNG_LOG("DUMP_VAR: {} = {}, {} = {}, {} = {}\n",           #v0, (v0), #v1, (v1), #v2, (v2)); } while(false)
#define LIBNG_DUMP_VAR_4(v0, v1, v2, v3)  do { LIBNG_LOG("DUMP_VAR: {} = {}, {} = {}, {} = {}, {} = {}\n",  #v0, (v0), #v1, (v1), #v2, (v2), #v3, (v3)); } while(false)

#define LIBNG_DUMP_VAR_SELECT(COUNT) LIBNG_DUMP_VAR_##COUNT

#define LIBNG_DUMP_VAR(...) LIBNG_IDENTITY(LIBNG_CALL(LIBNG_DUMP_VAR_SELECT, LIBNG_VA_ARGS_COUNT(__VA_ARGS__) (__VA_ARGS__)))