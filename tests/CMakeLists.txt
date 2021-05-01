cmake_minimum_required(VERSION 3.13.0)
project(CPP-React-Math-Tests)

set(Boost_FIND_REQUIRED ON)
set(Boost_DEBUG ON)
set(Boost_USE_STATIC_LIBS ON)

add_definitions(-DBOOST_ALL_NO_LIB) # disable boost auto linking

find_package(Boost COMPONENTS unit_test_framework REQUIRED)
link_directories(${Boost_LIBRARY_DIR_RELEASE})
include_directories(${Boost_INCLUDE_DIRS})

add_executable(test_unit
	tests_main.cpp
	matrix.cpp
	vector.cpp
	quat.cpp
)

target_link_libraries(test_unit CPP-React-Math)
target_link_libraries(test_unit ${Boost_LIBRARIES})