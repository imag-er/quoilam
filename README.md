# quoilam
![](icon.png)

## Introduction
Determined to build a c++ library like yazi.  
Containing threadpool socket async and other modules.
## Containing (increasing)
server & client (still improving)
singleton 
httpserver
stdlogger
database
threadpool 
## How to build
```shell
    git clone git@github.com:imag-er/quoilam.git
    cd quoilam && mkdir -p build && cd build  
    cmake .. && make
    # make install
```
## Install && Use
```shell
    make install
``` 
```cmake
# CMakeLists.txt
link_directories(/usr/include/quoilam/lib)
target_link_libraries(your_target_name PRIVATE 
    Httpserver
    StdLogger
    ...
)
```
## Modules
-> [Modules](MODULE.md)

## tips
the name, quoilam, is a mixture of french and my dialect,originates from my nickname while in high school