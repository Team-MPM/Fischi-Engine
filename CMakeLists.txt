cmake_minimum_required(VERSION 4.0)

project(module_test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler flags

add_compile_definitions(-D_LIBCPP_REMOVE_TRANSITIVE_INCLUDES)
add_compile_options(-fdiagnostics-color -Wall -Wextra -Wdeprecated
        -fexperimental-library -stdlib=libc++)
add_link_options(-fuse-ld=lld -stdlib=libc++ -Wl,--color-diagnostics -fdiagnostics-color
        -fexperimental-library -lm)
set(MOD_BASE_DIR /usr/local/share/libc++/v1)
add_compile_options(
        -Wno-reserved-module-identifier
        -Wno-reserved-user-defined-literal)
link_libraries(
        /usr/local/lib/x86_64-unknown-linux-gnu/libunwind.so
        /usr/local/lib/x86_64-unknown-linux-gnu/libc++.so)
include_directories(
        /usr/local/include
        /usr/local/include/c++/v1
        /usr/local/include/x86_64-unknown-linux-gnu/c++/v1)

# Packages

find_package(spdlog REQUIRED)
find_package(glm REQUIRED)

add_executable(sandbox)

target_include_directories(sandbox PRIVATE
        dependencies/spdlog/include
        dependencies/glm/glm)

target_sources(sandbox
        PUBLIC
        FILE_SET moduleStd
        TYPE CXX_MODULES
        BASE_DIRS ${MOD_BASE_DIR}
        FILES
        ${MOD_BASE_DIR}/std.cppm
        ${MOD_BASE_DIR}/std.compat.cppm)

target_sources(sandbox
        PUBLIC
        FILE_SET moduleGlm
        TYPE CXX_MODULES
        BASE_DIRS dependencies/glm/glm
        FILES
        dependencies/glm/glm/glm.cppm)

target_sources(sandbox
        PUBLIC
        FILE_SET moduleCore
        TYPE CXX_MODULES
        BASE_DIRS src/engine/core
        FILES
        src/engine/core/core.cppm
        src/engine/core/math.cppm
        src/engine/core/logger.cppm)

target_sources(sandbox PRIVATE
        src/sandbox/main.cpp)
