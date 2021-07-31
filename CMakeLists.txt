# CMakeList.txt : CMake project for solutions, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
 
project ("codesignal")

# Add source to this project's executable.
add_executable (codesignal "solutions.cpp" "solutions.h" "arrays.h" "linkedlist.h" "arcade.h" "data.cpp") 

# TODO: Add tests and install targets if needed.
