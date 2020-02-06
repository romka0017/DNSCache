cmake_minimum_required(VERSION 3.16)

project(DNSCache)

include_directories(../include)

set(SOURCE_LIB DNSCache.cpp)

add_library(DNSCache SHARED ${SOURCE_LIB})

target_link_libraries(DNSCache pthread)

set_property(TARGET DNSCache PROPERTY CXX_STANDARD 17)