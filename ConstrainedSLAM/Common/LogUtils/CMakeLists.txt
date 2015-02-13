add_library(Profiler private/CProfiler.cpp
                     private/CProfileManager.cpp
                     private/CProfileManager.hpp
                     CProfiler.hpp)
find_package(Boost COMPONENTS chrono system REQUIRED)
target_link_libraries(Profiler
   ${Boost_SYSTEM_LIBRARY}
   ${Boost_CHRONO_LIBRARY}
)
