cmake_minimum_required(VERSION 2.8)

project(SLAM)

#add ceres and it headers to project
LIST(APPEND INCLUDE_PATH "")
add_subdirectory(ceres-solver-1.9.0)
FOREACH(P ${INCLUDE_PATH}) 
	INCLUDE_DIRECTORIES(${P})
ENDFOREACH()

find_package(OpenCV REQUIRED)
find_package(Boost REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS})

add_subdirectory(test)


