:: remove prev files
rmdir /s /q build examples\build

:: create new build dir
mkdir build examples\build

:: build libs and install
cd build
cmake .. -G "MinGW Makefiles"
make
make install

:: build test examples
cd ..\examples\build
cmake .. -G "MinGW Makefiles"
make