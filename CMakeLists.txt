set(CMAKE_LEGACY_CYGWIN_WIN32 0) # Remove when CMake >= 2.8.4 is required
cmake_minimum_required(VERSION 3.13)
project(cpp_exercise)

set(CMAKE_CXX_STANDARD 14)

add_executable(cpp_exercise main.cpp)
