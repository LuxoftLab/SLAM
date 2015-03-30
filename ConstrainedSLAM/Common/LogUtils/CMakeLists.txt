add_library(Profiler private/CProfiler.cpp
                     private/CProfilesCollector.cpp
                     private/CProfilesCollector.hpp
                     CProfiler.hpp)
add_library(Logger   private/CLogger.hpp
                     private/CLogger.cpp
                     Logger.hpp)

find_package(Boost COMPONENTS chrono system REQUIRED)

target_link_libraries(Profiler
   ${Boost_SYSTEM_LIBRARY}
   ${Boost_CHRONO_LIBRARY}
)
