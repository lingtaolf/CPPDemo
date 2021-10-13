# cmake -B build .
# cmake --build build
#
cmake_minimum_required(VERSION 3.21)


project(demo VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

#include(${PROJECT_SOURCE_DIR}/contrib/CRoaring)
include(FetchContent)

FetchContent_Declare(
  roaring
  GIT_REPOSITORY git@github.com:RoaringBitmap/CRoaring.git
  GIT_TAG v0.2.66
  GIT_SHALLOW TRUE)

set(ENABLE_ROARING_TESTS OFF CACHE INTERNAL "")

set(ROARING_BUILD_STATIC ON CACHE INTERNAL "")
FetchContent_MakeAvailable(roaring)

FetchContent_GetProperties(roaring)
SET(CPP_ROARING_HEADERS ${roaring_SOURCE_DIR}/cpp/roaring64map.hh  ${roaring_SOURCE_DIR}/cpp/roaring.hh)
file(COPY  ${CPP_ROARING_HEADERS} DESTINATION ${roaring_SOURCE_DIR}/include/roaring)

add_executable(demo  ./src/main.cpp)
#add_executable(demo  ./src/test.cpp)
target_link_libraries(demo PUBLIC roaring)