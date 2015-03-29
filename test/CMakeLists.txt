
ADD_EXECUTABLE(trilateration trilateration.cpp)
TARGET_LINK_LIBRARIES(trilateration LINK_PUBLIC ceres)
target_link_libraries(trilateration ${OpenCV_LIBS})

ADD_EXECUTABLE(fundamentalMatrix fundamentalMatrix.cpp)
TARGET_LINK_LIBRARIES(fundamentalMatrix LINK_PUBLIC ceres)
target_link_libraries(fundamentalMatrix ${OpenCV_LIBS})
target_link_libraries(fundamentalMatrix PointTracker)

ADD_EXECUTABLE(simpleSba simpleSBA.cpp matrices.h)
TARGET_LINK_LIBRARIES(simpleSba LINK_PUBLIC ceres)
target_link_libraries(simpleSba ${OpenCV_LIBS})

ADD_EXECUTABLE(destructorTest destructorTest.cpp)
TARGET_LINK_LIBRARIES(destructorTest LINK_PUBLIC ceres)
