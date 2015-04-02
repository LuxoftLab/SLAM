add_executable(tracking private/tracking.cpp)

target_link_libraries(tracking ${OpenCV_LIBS})

target_link_libraries(tracking PointTracker)
