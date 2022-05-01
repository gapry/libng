target = libng_game

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

default: clean fmt build execute

clean:
ifeq ($(OS),Windows)
	IF EXIST build rmdir build /q /s
	IF EXIST *.cso DEL *.cso
	IF EXIST *.obj DEL *.obj
	IF EXIST *.exe DEL *.exe
	IF EXIST *.ilk DEL *.ilk
	IF EXIST *.pdb DEL *.pdb
else ifeq ($(OS),Linux)
	rm -rf build
else ifeq ($(OS),macOS)
	@echo "clean"
else
endif

fmt:
ifeq ($(OS),Windows)
	cd benchmark   & FOR /r %f IN (*.cpp *.hpp) do @clang-format -style=file -i %f & cd ..
	cd game        & FOR /r %f IN (*.cpp *.hpp) do @clang-format -style=file -i %f & cd ..
	cd libng       & FOR /r %f IN (*.cpp *.hpp) do @clang-format -style=file -i %f & cd ..
	cd test        & FOR /r %f IN (*.cpp *.hpp) do @clang-format -style=file -i %f & cd ..
	cd third_party & FOR /r %f IN (*.cpp *.hpp) do @clang-format -style=file -i %f & cd ..
else ifeq ($(OS),Linux)
	sh ./scripts/linux/fmt/format_on_linux.sh
else ifeq ($(OS),macOS)
	@echo "fmt"
else
endif

build:
ifeq ($(OS),Windows)
	mkdir build\game\shader
	fxc.exe /Od /Zi /T ps_5_0 /Fo .\build\game\shader\pixel.cso .\libng\shader\hlsl\pixel.hlsl
	fxc.exe /Od /Zi /T vs_5_0 /Fo .\build\game\shader\vertex.cso .\libng\shader\hlsl\vertex.hlsl
	cd build
	cmake -DBUILD_GAME=ON -G "NMake Makefiles" ..
	nmake 
	cd ..
else ifeq ($(OS),Linux)
	sh ./scripts/linux/build/build_on_linux.sh
else ifeq ($(OS),macOS)
	@echo "build"
else
endif

tests:
ifeq ($(OS),Windows)
	mkdir build
	cd build
	cmake -DBUILD_TEST=ON -G "NMake Makefiles" ..
	nmake 
	cd ..
	.\build\test\libng_test.exe
else ifeq ($(OS),Linux)
	sh ./scripts/linux/test/unittest.sh
else ifeq ($(OS),macOS)
	@echo "tests"
else
endif

execute:
ifeq ($(OS),Windows)
	.\build\game\$(target).exe
else ifeq ($(OS),Linux)
	sh ./scripts/linux/execute/execute_on_linux.sh
else ifeq ($(OS),macOS)
	@echo "execute"
else
endif

.PHONY: default clean fmt build tests execute
