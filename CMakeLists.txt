
cmake_minimum_required(VERSION 3.0)

project(mapper)

include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})

set(CXX_FLAGS "-Wall -pipe -std=c++14")
string(REPLACE ";" " " CXX_FLAGS " ${CXX_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_FLAGS}" CACHE string "" FORCE)

add_library(mapper SHARED mapper.cpp node.cpp edge.cpp path.cpp)

add_executable(dbg test/debug.cpp)
target_link_libraries(dbg mapper)

#############################################################################
# Testing

option(BUILD_TESTS "Собрать и запустить модульное тестирование" OFF)

if(BUILD_TESTS)

	enable_testing()

	add_executable(run_tests test/test.cpp)
	target_link_libraries(run_tests mapper ${GDAL_LIBRARY} pthread gmock gmock_main gtest gtest_main)
	add_test(html-tests run_tests)

endif()

