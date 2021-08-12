# CMakeList.txt : CMake project for solutions, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)


SET(PATH_TO_JSONRAPID "G:/projects/vcpkg/installed/x86-windows/include") 

message(STATUS ${PATH_TO_JSONRAPID})

include_directories(${PATH_TO_JSONRAPID}) 

project ("codesignal")
 


# Add source to this project's executable.
add_executable (codesignal "solutions.cpp" "solutions.h" "arrays.h" "linkedlist.h" "arcade.h" "data.cpp" "hashtables.h" "json.hpp" ) 

# TODO: Add tests and install targets if needed.
