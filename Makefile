# Ref: https://stackoverflow.com/questions/8270391/use-the-same-makefile-for-make-linux-and-NMAKE.exe-windows

ifdef MAKEDIR: # GNU Make is false,        NMAKE.exe.exe is unused target.
!ifdef MAKEDIR # GNU Make doesn't seen it, NMAKE.exe.exe is true.

clean:
	call .\scripts\win32\clean.bat

fmt:
	call .\scripts\win32\fmt.bat

build_game:
	call .\scripts\win32\build\game.bat

build_tests:
	call .\scripts\win32\build\tests.bat

tests:
	call .\scripts\win32\unit_test.bat

execute:
	call .\scripts\win32\execute.bat

vcpkg:
	call .\scripts\win32\vcpkg.bat

!else 
else

ifeq ($(OS),Windows_NT)
	OS = Windows
else
	UNAME := $(shell uname -s)
	ifeq ($(UNAME),Darwin)
		OS = macOS
	else ifeq ($(UNAME),Linux)
		OS = Linux
	else
	endif
endif

clean:
ifeq ($(OS),Windows)
	call .\scripts\win32\clean.bat
else ifeq ($(OS),Linux)
	rm -rf build
else ifeq ($(OS),macOS)
	@echo "clean"
else
endif

fmt:
ifeq ($(OS),Windows)
	call .\scripts\win32\fmt.bat
else ifeq ($(OS),Linux)
	sh ./scripts/linux/format_on_linux.sh
else ifeq ($(OS),macOS)
	@echo "fmt"
else
endif

build:
ifeq ($(OS),Windows)
	call .\scripts\win32\build.bat
else ifeq ($(OS),Linux)
	sh ./scripts/linux/build_on_linux.sh
else ifeq ($(OS),macOS)
	@echo "build"
else
endif

tests:
ifeq ($(OS),Windows)
	call .\scripts\win32\unit_test.bat
else ifeq ($(OS),Linux)
	sh ./scripts/linux/unittest.sh
else ifeq ($(OS),macOS)
	@echo "tests"
else
endif

execute:
ifeq ($(OS),Windows)
	call .\scripts\win32\execute.bat
else ifeq ($(OS),Linux)
	sh ./scripts/linux/execute_on_linux.sh
else ifeq ($(OS),macOS)
	@echo "execute"
else
endif

endif    # GNU Make is the close condition, NMAKE.exe doesn't seen it.
!endif : # GNU Make is the unused target,   NMAKE.exe is the close conditional.

default: clean fmt build execute

.PHONY: default clean fmt build tests execute