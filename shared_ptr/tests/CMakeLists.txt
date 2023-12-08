cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(Tests LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    main_test.cpp
    shared_ptr_test.cpp
    stack_allocator_test.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

set(BINARY_NAME tests${CMAKE_PROJECT_NAME})
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
    GTest::gtest
    GTest::gmock)

include_directories(${CMAKE_SOURCE_DIR}/include)