# CMake Version
cmake_minimum_required(VERSION 3.23.2)
# Project Name
project(mkr_log_lib)

# Includes
include(FetchContent)

# C++ Version
set(CMAKE_CXX_STANDARD 20)

# Compiler Flags
set(CMAKE_CXX_FLAGS "-std=c++20 -O3")

# Compiler Flags
# set(CMAKE_CXX_FLAGS "-std=c++20 -O3")

set(SRC_DIR "src/")
file(GLOB_RECURSE SRC_FILES LIST_DIRECTORIES true CONFIGURE_DEPENDS
        "${SRC_DIR}/*.h"
        "${SRC_DIR}/*.c"
        "${SRC_DIR}/*.hpp"
        "${SRC_DIR}/*.cpp")
add_library(${PROJECT_NAME} ${SRC_FILES})

# External Dependencies
# spdlog: https://github.com/gabime/spdlog
FetchContent_Declare(spdlog GIT_REPOSITORY https://github.com/gabime/spdlog.git GIT_TAG da14258533cb951ce85087ceb45556e0b8253660)
FetchContent_MakeAvailable(spdlog)

# Target
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(${PROJECT_NAME} PUBLIC ${SRC_DIR})
target_link_libraries(${PROJECT_NAME} spdlog)
