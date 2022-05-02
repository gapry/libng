mkdir build
cd build
cmake -DBUILD_TEST=ON -G "NMake Makefiles" ..
nmake 
cd ..
.\build\test\libng_test.exe