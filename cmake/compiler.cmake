if(LINUX)
set(CMAKE_C_COMPILER   "clang")
set(CMAKE_CXX_COMPILER "clang++")
endif(LINUX)

if(MSVC)
set(CMAKE_C_COMPILER        "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.31.31103\\bin\\Hostx86\\x86\\cl.exe")
set(CMAKE_CXX_COMPILER      "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.31.31103\\bin\\Hostx86\\x86\\cl.exe")
set(CMAKE_CXX_FLAGS         "/nologo /MP /Zi /EHsc /D_UNICODE /DUNICODE /DWIN32 /D_WINDOWS")
set(CMAKE_EXE_LINKER_FLAGS  "/link /subsystem:console user32.lib gdi32.lib")
endif(MSVC)

set(CMAKE_CXX_STANDARD          17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

include(ProcessorCount)
ProcessorCount(NPROC)
set(CMAKE_CXX_FLAGS_INIT "-j${NPROC}")
