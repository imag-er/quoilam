# remove prev files
sudo rm -rf build examples/build

# create new build dir
mkdir -p build examples/build

# build libs and install
cd build
cmake ..
make
sudo make install

# build test examples
cd ../examples/build
cmake ..
make
