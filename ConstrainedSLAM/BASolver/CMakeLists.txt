
add_library(BASolver IBASolver.hpp CBASolver.hpp
                     private/CBASolver.cpp
                     private/AFunctor.cpp
                     private/CBothMutable.cpp
                     private/CConstCamera.cpp
                     private/CFunctorContainer.cpp
                     private/AFunctor.hpp
                     private/CBothMutable.hpp
                     private/CConstCamera.hpp
                     private/CFunctorContainer.hpp)

target_link_libraries(BASolver LINK_PUBLIC ceres)
target_link_libraries(BASolver Scene3D)
