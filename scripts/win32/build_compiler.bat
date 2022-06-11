mkdir build
cd build

cmake -DBUILD_COMPILER=ON -DIDE_VSC=ON -GNinja ..
ninja
cd ..