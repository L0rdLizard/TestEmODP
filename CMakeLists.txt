cmake_minimum_required(VERSION 3.28)
project(TestEmODP)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)

pkg_check_modules(YOUR_LIBRARY REQUIRED libemodp)

add_executable(TestEmODP
        hello.cpp)

target_include_directories(TestEmODP PUBLIC ${YOUR_LIBRARY_INCLUDE_DIRS})
target_link_libraries(TestEmODP ${YOUR_LIBRARY_LIBRARIES})
