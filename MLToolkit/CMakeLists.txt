cmake_minimum_required(VERSION 3.15)
project(MLToolkit VERSION 1.0)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(lib/googletest)