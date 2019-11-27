cmake_minimum_required(VERSION 3.0.0)
project(cubot_cv_test VERSION 0.1.0)

include(CTest)
enable_testing()

find_package( OpenCV REQUIRED )
add_executable(cubot_cv_test cubot_cv_test.cpp)

target_link_libraries(opencv_test ${OpenCV_LIBS} )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


