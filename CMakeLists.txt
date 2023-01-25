cmake_minimum_required(VERSION 3.15)

project(try_sfml VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(USE_VCPKG "Whether to use VCPCKG" ON)
if(USE_VCPKG)
    message("Using VCPKG")
    include(${CMAKE_SOURCE_DIR}/external/vcpkg/scripts/buildsystems/vcpkg.cmake)
endif()

add_subdirectory(src)

option(USE_TESTS "Build tests" ON)
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND USE_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()