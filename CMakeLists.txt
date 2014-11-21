cmake_minimum_required(VERSION 2.8)

project(SLAM)
LIST(APPEND INCLUDE_PATH "")
add_subdirectory(ceres-solver-1.9.0)
FOREACH(P ${INCLUDE_PATH}) 
	INCLUDE_DIRECTORIES(${P})
ENDFOREACH()
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
add_subdirectory(test)


