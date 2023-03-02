# quoilam
### Introduction
Determined to build a c++ library like yazi.  
Containing threadpool socket async and other modules.
### Containing (increasing)
server & client (now available but still improving)
singleton 
threadpool (unfinished)
### Name meaning
quoilam,a mixture of french and my dialect,is my nickname while in high school
### How to build
```shell
    git clone git@github.com:imag-er/quoilam.git
    cd quoilam && mkdir -p build && cd build  
    cmake .. && make
    # make install
```
### Use
- **test**
 After run ```cmake .. && make``` 
 just use ```./executables/testexec``` to test.
 If the output is "success",represents the project was successfully built.
- **integrate in your project**
  - **step1**  
    add  
    ```cmake
    set(quoilam_source_dir 
        #where the source dir is
    )
    link_directory( 
        ${quoilam_source_dir}/build/library/
    )
    include_directory(
        ${quoilam_source_dir}/src/include/
        )
    ```
    to your *CMakeLists.txt*.
   - **step2**
        Then just add the quoilam libs into your executable target's dependencies like 
        ```cmake
        add_executable(some_target
            PUBLIC
            server
            singleton
            ...
        )
        ```
        and build your project.That's finished.
    
- **install** (under development)  
    just run ```make install``` And then go to step2.