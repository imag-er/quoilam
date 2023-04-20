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
    cd quoilam
    ./build.sh
```
## Use
```cmake
# CMakeLists.txt
find_package(quoilam REQUIRED)
include_directories(/usr/local/include/quoilam/include/)


# example
add_executable(myserver myserver.cpp)
target_link_libraries(myserver quoilam::Server)

```
## Sturcture
## namespace:
## quoilam  
- ### network   
- - ### Server
- - ### Client
- - ### HttpServer
- ### ultility  
- - ### ThreadPool
- - ### Database
- - ### Pipe
- - ### Singleton
- ### io
- - ### StdLogger
- - ### 
- ### text
- - ### Json
## tips
the name, quoilam, is a mixture of french and my dialect,originates from my nickname while in high school
