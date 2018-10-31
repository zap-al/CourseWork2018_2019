cmake_minimum_required(VERSION 2.8)

project( DisplayImage )

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS}, ./ )

SET(HEAER interface.h)
SET(SOURCE realize.cpp)

add_library(interface STATIC realize.cpp)

add_executable( DisplayImage DisplayImage.cpp realize.cpp )

target_link_libraries( DisplayImage ${OpenCV_LIBS})
target_link_libraries( DisplayImage interface )