mkdir build\game\shader
fxc.exe /Od /Zi /T ps_5_0 /Fo .\build\game\shader\pixel.cso .\libng\shader\hlsl\pixel.hlsl
fxc.exe /Od /Zi /T vs_5_0 /Fo .\build\game\shader\vertex.cso .\libng\shader\hlsl\vertex.hlsl
cd build
cmake -DBUILD_GAME=ON -G "NMake Makefiles" ..
nmake 
cd ..