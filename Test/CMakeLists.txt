cmake_minimum_required(VERSION 3.28.0)
project(reflection_test VERSION 0.1.0 LANGUAGES C CXX)

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz)
FetchContent_MakeAvailable(json)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.8.1
)
FetchContent_MakeAvailable(Catch2)

add_executable( reflection_test ${CMAKE_CURRENT_LIST_DIR}/test.cpp )
target_include_directories(reflection_test PRIVATE ${CMAKE_CURRENT_LIST_DIR}/..)

target_link_libraries( reflection_test PRIVATE nlohmann_json::nlohmann_json Catch2::Catch2WithMain)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++26 -freflection" )

include(CTest)
include(Catch)
catch_discover_tests(reflection_test)