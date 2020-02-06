cmake_minimum_required(VERSION 3.16)

project(test_DNSCache)

include_directories(include)
include_directories(libs)

set(SOURCE_EXE catch_tests.cpp)

add_executable(catch_tests ${SOURCE_EXE})
add_subdirectory(src)

target_link_libraries(catch_tests DNSCache)

set_property(TARGET catch_tests PROPERTY CXX_STANDARD 17)