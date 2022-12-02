cmake_minimum_required(VERSION 3.0.0)
project(os-3 VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) 
find_package(Threads REQUIRED)

set(SRC_FILES main.cpp src/fork.h src/fork.cpp src/philosopher.h src/philosopher.cpp)
add_executable(dine ${SRC_FILES})
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)