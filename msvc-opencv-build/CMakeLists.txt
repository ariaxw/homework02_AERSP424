cmake_minimum_required(VERSION 3.16)
project(hw2)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

list(APPEND CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/third_party/opencv/install")
set(OpenCV_DIR "${PROJECT_SOURCE_DIR}/third_party/build_opencv")


find_package(OpenCV REQUIRED PATHS "${OpenCV_DIR}")

include_directories(
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/src
  ${OpenCV_INCLUDE_DIRS}
)

file(GLOB all_SRCS
  "${PROJECT_SOURCE_DIR}/include/*.h"
  "${PROJECT_SOURCE_DIR}/include/*.hpp"
  "${PROJECT_SOURCE_DIR}/src/*.cpp"
  "${PROJECT_SOURCE_DIR}/src/*.c"
)

add_executable(${CMAKE_PROJECT_NAME} ${all_SRCS})
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})



