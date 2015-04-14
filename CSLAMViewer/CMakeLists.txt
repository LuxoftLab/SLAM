add_executable(tracking private/tracking.cpp)

target_link_libraries(tracking ${OpenCV_LIBS})

TARGET_LINK_LIBRARIES(tracking LINK_PUBLIC ceres)
target_link_libraries(tracking PointTracker)
target_link_libraries(tracking BASolver)
