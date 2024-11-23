cmake_minimum_required(VERSION 3.22)
project(homework02_AERSP424
    DESCRIPTION "Homework 02 Solution Set for AERSP424"
    VERSION 1.0.0)

# Set C++ standard and compiler flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

# Print current source directory
message(STATUS "CMakeLists.txt is at ${PROJECT_SOURCE_DIR}")

# Dependencies
find_package(OpenGL REQUIRED)

# Add GLEW
set(GLEW_INCLUDE_DIR /opt/homebrew/Cellar/glew/2.2.0_1/include)
set(GLEW_LIBRARY /opt/homebrew/Cellar/glew/2.2.0_1/lib/libGLEW.dylib)

include_directories(${GLEW_INCLUDE_DIR})
link_directories(/opt/homebrew/Cellar/glew/2.2.0_1/lib)

# Add GLFW
list(APPEND CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/third_party/glfw/install")
find_package(glfw3 REQUIRED)

# Add Matplot++
list(APPEND CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/third_party/matplotplusplus/install")
find_package(Matplot++ REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror")

# Include directories
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
)

# Build separate executables for each question
add_executable(Question1 src/Question1.cpp)
target_link_libraries(Question1 OpenGL::GL glfw ${GLEW_LIBRARY} Matplot++::matplot pthread)

add_executable(Question2 src/Question2.cpp)
target_link_libraries(Question2 OpenGL::GL glfw ${GLEW_LIBRARY} Matplot++::matplot pthread)

add_executable(Question3 src/Question3.cpp)
target_link_libraries(Question3 OpenGL::GL glfw ${GLEW_LIBRARY} Matplot++::matplot pthread)

add_executable(Question4 src/Question4.cpp)
target_link_libraries(Question4 OpenGL::GL glfw ${GLEW_LIBRARY} Matplot++::matplot pthread)

# Install configuration
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})
install(TARGETS Question1 Question2 Question3 Question4
    RUNTIME DESTINATION bin
)

# Enable packaging
set(CPACK_PROJECT_NAME ${CMAKE_PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${CMAKE_PROJECT_VERSION})
set(CPACK_GENERATOR "ZIP;TGZ")
set(CPACK_SOURCE_IGNORE_FILES
    /.git
    /dist
    /results
    /.*build.*
    /\\\\.DS_Store
)
set(CPACK_ARCHIVE_COMPONENT_INSTALL 1)
include(CPack)
