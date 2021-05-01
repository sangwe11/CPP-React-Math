cmake_minimum_required(VERSION 3.13.0)
project (CPP-React-Math)
set(CMAKE_CXX_STANDARD 14)

option(build_example "Build example" ON)
option(build_tests "Build tests" ON)

add_library(CPP-React-Math INTERFACE)
target_include_directories(CPP-React-Math INTERFACE include)

add_subdirectory(include)

if(build_example)
	add_subdirectory(example)
endif()

if(build_tests)
	add_subdirectory(tests)
endif()