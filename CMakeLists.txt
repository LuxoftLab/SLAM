cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )
add_compile_options(-std=c++11)
project(SLAM)

#add ceres and it headers to project
LIST(APPEND INCLUDE_PATH "")
add_subdirectory(ceres-solver-1.9.0)
FOREACH(P ${INCLUDE_PATH}) 
	INCLUDE_DIRECTORIES(${P})
ENDFOREACH()

find_package(OpenCV REQUIRED)
find_package(Boost REQUIRED)

INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(test)
INCLUDE_DIRECTORIES(ConstrainedSLAM)

add_subdirectory(test)
add_subdirectory(ConstrainedSLAM)
add_subdirectory(CSLAMViewer)

