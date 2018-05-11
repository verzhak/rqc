
cmake_minimum_required(VERSION 3.0)

project(mapper)

find_package(PkgConfig)

include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})

set(CXX_FLAGS "-Werror -pipe -std=c++14")
string(REPLACE ";" " " CXX_FLAGS " ${CXX_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_FLAGS}" CACHE string "" FORCE)

add_library(mapper SHARED mapper.cpp node.cpp edge.cpp path.cpp)

add_executable(dbg test/debug.cpp)
target_link_libraries(dbg mapper)

#############################################################################
# Тесты

option(BUILD_TESTS "Собрать и запустить модульное тестирование" OFF)

if(BUILD_TESTS)

	pkg_check_modules(GTEST REQUIRED gtest)

	enable_testing()

	add_executable(run_tests test/test.cpp)
	target_link_libraries(run_tests mapper ${GTEST_LIBRARIES})

	add_test(NAME test COMMAND run_tests)

endif()

#############################################################################
# Документация

option(BUILD_DOC "Сборка документации" OFF)

if(BUILD_DOC)

	find_package(Doxygen)

	if(DOXYGEN_FOUND)

		add_custom_target(doc ALL
			COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
			WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
			VERBATIM)

	endif()

endif()

