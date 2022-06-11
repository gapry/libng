mkdir build
cd build

::cmake -DBUILD_TEST=ON -G "NMake Makefiles" ..
::nmake 

cmake -DBUILD_TEST=ON -DIDE_VSC=ON -GNinja ..
ninja
cd ..