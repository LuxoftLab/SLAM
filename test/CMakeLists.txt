
ADD_EXECUTABLE(trilateration trilateration.cpp interfaces.h)
TARGET_LINK_LIBRARIES(trilateration LINK_PUBLIC ceres)
target_link_libraries(trilateration ${OpenCV_LIBS})
