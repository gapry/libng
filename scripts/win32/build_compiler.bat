mkdir build
cd build

cmake -DBUILD_COMPILER=ON -DIDE_VSC=ON -D CMAKE_C_COMPILER="cl.exe" -D CMAKE_CXX_COMPILER="cl.exe" -GNinja ..
ninja
cd ..