mkdir build
cd build
::cmake -DBUILD_TEST=ON -G "NMake Makefiles" ..
::nmake 
cmake -DBUILD_TEST=ON -GNinja ..
ninja
cd ..
.\build\test\libng_test.exe