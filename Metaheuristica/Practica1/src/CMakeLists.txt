cmake_minimum_required(VERSION 3.0)
project(Practica1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(include)

set(SOURCE_FILES
        ${PROJECT_SOURCE_DIR}/main.cpp
        ${PROJECT_SOURCE_DIR}/MQKPEvaluator.cpp
        ${PROJECT_SOURCE_DIR}/MQKPInstance.cpp
        ${PROJECT_SOURCE_DIR}/MQKPSolGenerator.cpp
        ${PROJECT_SOURCE_DIR}/MQKPSolution.cpp
        ${PROJECT_SOURCE_DIR}/seeds.cpp
        ${PROJECT_SOURCE_DIR}/Timer.cpp
        )

add_executable(practica1 ${SOURCE_FILES})