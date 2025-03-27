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

# Functions

function(add_module TARGET NAME BASE_DIR)
    target_sources(${TARGET}
            PUBLIC
            FILE_SET ${NAME}
            TYPE CXX_MODULES
            BASE_DIRS ${BASE_DIR}
            FILES ${ARGN})
endfunction()

# File sets

set(STD_FILES
        ${MOD_BASE_DIR}/std.cppm
        ${MOD_BASE_DIR}/std.compat.cppm)
set(STD_FILES_DIR ${MOD_BASE_DIR})

set(GLM_FILES
        dependencies/glm/glm/glm.cppm)
set(GLM_FILES_DIR dependencies/glm/glm)

set(CORE_FILES
        src/engine/core/core.cppm
        src/engine/core/app.cppm
        src/engine/core/service.cppm
        src/engine/core/di.cppm
        src/engine/core/events.cppm
        src/engine/core/math.cppm
        src/engine/core/logger.cppm)
set(CORE_FILES_DIR src/engine/core)

set (SANDBOX_FILES
        src/sandbox/main.cpp)

# Sandbox

target_include_directories(sandbox PRIVATE
        dependencies/spdlog/include
        dependencies/glm/glm)

add_module(sandbox moduleStd ${STD_FILES_DIR} ${STD_FILES})
add_module(sandbox moduleGlm ${GLM_FILES_DIR} ${GLM_FILES})
add_module(sandbox moduleCore ${CORE_FILES_DIR} ${CORE_FILES})

target_sources(sandbox PRIVATE ${SANDBOX_FILES})
