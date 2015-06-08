

add_subdirectory(Tracker)
add_library(PointTracker private/CPointTracker.cpp IPointTracker.hpp CPointTracker.hpp)

target_link_libraries(PointTracker OpticalFlow)
target_link_libraries(PointTracker SteinTracker)
target_link_libraries(PointTracker Common)
