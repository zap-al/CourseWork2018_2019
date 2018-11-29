cmake_minimum_required(VERSION 2.8)

project( DisplayImage )

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS}, ./ , ./Interface )

SET(HEADER CrossFindingInterface.h)
SET(SOURCE CrossFindingRealize.cpp)

SET(HEADER ImgManipInterface.h)
SET(SOURCE ImgManipRealize.cpp)

SET(HEADER StructuresInterface.h)
SET(SOURCE StructuresRealize.cpp)

SET(HEADER BasisDecompositionInterface.h)
SET(SOURCE BasisDecompositionRealize.cpp)

add_library(CrossFindingInterface STATIC Realization/CrossFindingRealize.cpp)
add_library(ImgManipInterface STATIC Realization/ImgManipRealize.cpp)
add_library(StructuresInterface STATIC Realization/StructuresRealize.cpp)
add_library(BasisDecompositionInterface STATIC Realization/BasisDecompositionRealize.cpp)

SET(EXECUTABLE_OUTPUT_PATH ../)

add_executable( DisplayImage Start.cpp 
                Realization/CrossFindingRealize.cpp 
                Realization/ImgManipRealize.cpp 
                Realization/StructuresRealize.cpp 
                Realization/BasisDecompositionRealize.cpp)

target_link_libraries( DisplayImage ${OpenCV_LIBS})
target_link_libraries( DisplayImage CrossFindingInterface )
target_link_libraries( DisplayImage ImgManipInterface )
target_link_libraries( DisplayImage StructuresInterface )
target_link_libraries( DisplayImage BasisDecompositionInterface )