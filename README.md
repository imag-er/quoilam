# quoilam
![](icon.png)

## Introduction
Toy
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
- ### util  
- - ### ThreadPool
- - ### Database
- - ### Pipe
- - ### Singleton
- - ### Except
- ### io
- - ### StdLogger
- - ### 
- ### text
- - ### Json
## tips
the name, quoilam, is a mixture of french and my dialect,originates from my nickname while in high school
