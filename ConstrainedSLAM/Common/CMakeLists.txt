add_subdirectory(LogUtils)

add_library(Common private/CFrame.cpp CFrame.hpp Common.hpp)
target_link_libraries(Common Profiler)
