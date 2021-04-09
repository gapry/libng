if(LINUX)
set(CMAKE_C_COMPILER   "clang")
set(CMAKE_CXX_COMPILER "clang++")
endif(LINUX)

if(MSVC)
set(CMAKE_C_COMPILER   "cl")
set(CMAKE_CXX_COMPILER "cl")
endif(MSVC)

set(CMAKE_CXX_STANDARD          17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

include(ProcessorCount)
ProcessorCount(NPROC)
set(CMAKE_CXX_FLAGS_INIT "-j${NPROC}")
