# Fundamentos de Sistemas Inteligentes en Vision

cmake_minimum_required (VERSION 3.0)
project (image_classifier)
set(CMAKE_CXX_FLAGS "-std=c++11")
find_package(OpenCV 3.1 REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/tclap-1.2.1/include ${OpenCV_INCLUDE_DIRS})
LINK_LIBRARIES(${OpenCV_LIBS})

# For students
add_executable(train_bovw train_bovw.cpp common_code.cpp common_code.hpp)
add_executable(test_bovw test_bovw.cpp common_code.cpp common_code.hpp)
