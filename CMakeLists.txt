#
# EOS
# Copyright 2014 Gracjan Olbinski. Some rights reserved.
#
cmake_minimum_required(VERSION 2.8.8)
project(eos)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB_RECURSE eos_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc
)

enable_testing()
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test/gmock)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/test/gmock/include
  ${CMAKE_CURRENT_SOURCE_DIR}/test/gmock/gtest/include
)

file(GLOB_RECURSE eos_TEST_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/test/tests/*.h
  ${CMAKE_CURRENT_SOURCE_DIR}/test/tests/*.cc
)

add_executable(eos-tests ${eos_SOURCES} ${eos_TEST_SOURCES})

target_link_libraries(eos-tests
  gtest
  gtest_main
  gmock
  pthread
)

add_test(
  NAME              eos-tests-unit
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMAND           eos-tests
)

add_custom_target(eos-tests-run
  COMMAND eos-tests --gtest_output=xml:${CMAKE_CURRENT_BINARY_DIR}/eos-tests-results.xml
  DEPENDS eos-tests
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMENT "Executing tests..."
)

add_custom_command(TARGET eos-tests-run POST_BUILD
  COMMAND ;
  COMMENT "Summary available at: ${CMAKE_CURRENT_BINARY_DIR}/eos-tests-results.xml"
)