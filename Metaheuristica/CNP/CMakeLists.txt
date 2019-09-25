cmake_minimum_required(VERSION 3.0)
project(CNP)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -g -I /usr/local/Cellar/boost/1.69.0 -w")

include_directories(src/include)

set(SOURCE_FILES
        ${PROJECT_SOURCE_DIR}/src/main.cpp
        ${PROJECT_SOURCE_DIR}/src/CNPInstance.cpp
        ${PROJECT_SOURCE_DIR}/src/CNPEvaluator.cpp
        ${PROJECT_SOURCE_DIR}/src/CNPSolGenerator.cpp
        ${PROJECT_SOURCE_DIR}/src/CNPSolution.cpp
        ${PROJECT_SOURCE_DIR}/src/funcionesAuxiliares.cpp
        ${PROJECT_SOURCE_DIR}/src/CNPObjectAssignmentOperation.cpp
        ${PROJECT_SOURCE_DIR}/src/seeds.cpp
        ${PROJECT_SOURCE_DIR}/src/Timer.cpp        
        ${PROJECT_SOURCE_DIR}/src/CNPSimulatedAnnealing.cpp
        ${PROJECT_SOURCE_DIR}/src/CNPNodeAssignmentOperation.cpp
        ${PROJECT_SOURCE_DIR}/src/CNPTabuSearch.cpp
        )

add_executable(CNP ${SOURCE_FILES})