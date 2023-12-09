cmake_minimum_required(VERSION 3.14)

set(SOURCES main.cpp)

include_directories(${PROJECT_SOURCE_DIR}/include)
add_executable(${PROJECT_NAME} ${SOURCES})