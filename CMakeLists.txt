# CMakeList.txt : CMake project for solutions, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
 
project ("solutions")

# Add source to this project's executable.
add_executable (solutions "solutions.cpp" "solutions.h" "arrays.h" "linkedlist.h")

# TODO: Add tests and install targets if needed.
