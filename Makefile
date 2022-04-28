target = libng_game

default: clean fmt build execute

execute:
	.\build\game\$(target).exe

build:
	mkdir build\game\shader
	fxc.exe /Od /Zi /T ps_5_0 /Fo .\build\game\shader\pixel.cso .\libng\shader\hlsl\pixel.hlsl
	fxc.exe /Od /Zi /T vs_5_0 /Fo .\build\game\shader\vertex.cso .\libng\shader\hlsl\vertex.hlsl
	cd build
	cmake -DBUILD_GAME=ON -G "NMake Makefiles" ..
	nmake 
	cd ..

clean:
	IF EXIST build rmdir build /q /s
	IF EXIST *.cso DEL *.cso
	IF EXIST *.obj DEL *.obj
	IF EXIST *.exe DEL *.exe
	IF EXIST *.ilk DEL *.ilk
	IF EXIST *.pdb DEL *.pdb

fmt:
	FOR %f IN (*.cpp *.hpp) do @clang-format -style=file -i %f

.PHONY: default execute build clean fmt 