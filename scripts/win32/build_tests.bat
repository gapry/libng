mkdir build
cd build

::cmake -DBUILD_TEST=ON -G "NMake Makefiles" ..
::nmake 

cmake -DBUILD_TEST=ON -DIDE_VSC=ON -D CMAKE_C_COMPILER="cl.exe" -D CMAKE_CXX_COMPILER="cl.exe" -GNinja ..
ninja
cd ..