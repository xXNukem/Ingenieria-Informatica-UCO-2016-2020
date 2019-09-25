cmake_minimum_required(VERSION 3.0)
project(Practica4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(src/include)

set(SOURCE_FILES
        ${PROJECT_SOURCE_DIR}/src/main.cpp
        ${PROJECT_SOURCE_DIR}/src/MQKPEvaluator.cpp        
        ${PROJECT_SOURCE_DIR}/src/MQKPObjectAssignmentOperation.cpp   
        ${PROJECT_SOURCE_DIR}/src/MQKPInstance.cpp
        ${PROJECT_SOURCE_DIR}/src/MQKPSolGenerator.cpp
        ${PROJECT_SOURCE_DIR}/src/MQKPSolution.cpp
        ${PROJECT_SOURCE_DIR}/src/seeds.cpp
        ${PROJECT_SOURCE_DIR}/src/Timer.cpp
        )

add_executable(practica4 ${SOURCE_FILES})