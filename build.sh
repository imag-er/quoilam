# build libs and install
cd build
cmake ..
make
sudo make install

# build test examples
cd ../examples/build
cmake ..
make
