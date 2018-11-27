cmake_minimum_required(VERSION 2.8)

project( DisplayImage )

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS}, ./ )

SET(HEADER CrossFindingInterface.h)
SET(SOURCE CrossFindingRealize.cpp)

SET(HEADER FocusFindingInterface.h)
SET(SOURCE FocusFindingRealize.cpp)

SET(HEADER ImgManipInterface.h)
SET(SOURCE ImgManipRealize.cpp)

SET(HEADER StructuresInterface.h)
SET(SOURCE StructuresRealize.cpp)

SET(HEADER BasisDecompositionInterface.h)
SET(SOURCE BasisDecompositionRealize.cpp)

add_library(CrossFindingInterface STATIC CrossFindingRealize.cpp)
add_library(FocusFindingInterface STATIC FocusFindingRealize.cpp)
add_library(ImgManipInterface STATIC ImgManipRealize.cpp)
add_library(StructuresInterface STATIC StructuresRealize.cpp)
add_library(BasisDecompositionInterface STATIC BasisDecompositionRealize.cpp)

SET(EXECUTABLE_OUTPUT_PATH ./)


add_executable( DisplayImage Start.cpp CrossFindingRealize.cpp FocusFindingRealize.cpp ImgManipRealize.cpp StructuresRealize.cpp BasisDecompositionRealize.cpp)

target_link_libraries( DisplayImage ${OpenCV_LIBS})
target_link_libraries( DisplayImage CrossFindingInterface )
target_link_libraries( DisplayImage FocusFindingInterface )
target_link_libraries( DisplayImage ImgManipInterface )
target_link_libraries( DisplayImage StructuresInterface )
target_link_libraries( DisplayImage BasisDecompositionInterface )