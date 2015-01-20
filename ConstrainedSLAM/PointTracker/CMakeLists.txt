

add_subdirectory(Tracker)
add_library(PointTracker private/PointTracker.cpp PointTracker.h)

target_link_libraries(PointTracker OpticalFlow)
target_link_libraries(PointTracker Common)
