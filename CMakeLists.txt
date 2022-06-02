cmake_minimum_required(VERSION 3.10)

# set the project name
project(librsvgminimal)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
find_package(LibRSVG)
include_directories(${LibRSVG_INCLUDE_DIRS})
# add the executable
add_executable(librsvgminimal main.cpp)
target_link_libraries( librsvgminimal ${LibRSVG_LIBRARIES} )
set(CMAKE_CXX_STANDARD 11)