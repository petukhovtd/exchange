cmake_minimum_required(VERSION 3.5)

include(cmake/utils.cmake)

exchange_extract_version()

project(exchange VERSION ${EXCHANGE_VERSION} LANGUAGES CXX)
message(STATUS "Build ${PROJECT_NAME}: ${EXCHANGE_VERSION}")

if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 14)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

option(EXCHANGE_BUILD_TESTS "Build tests" OFF)
option(EXCHANGE_BUILD_SHARED "Build shared library" OFF)
option(EXCHANGE_BUILD_EXAMPLE "Build example" OFF)

if(NOT DEFINED EXCHANGE_MASTER_PROJECT)
    if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
        set(EXCHANGE_MASTER_PROJECT ON)
        set(EXCHANGE_BUILD_TESTS ON)
        set(EXCHANGE_BUILD_EXAMPLE ON)
    else()
        set(EXCHANGE_MASTER_PROJECT OFF)
    endif()
endif()

add_subdirectory(contrib)

set(SOURCE
        src/actor_storage_table.cpp
        src/actor_storage_line.cpp
        src/id_generator_forward.cpp
        src/id_generator_reuse.cpp
        src/exchange.cpp
)

if(EXCHANGE_BUILD_SHARED OR BUILD_SHARED_LIBS)
    add_library(${PROJECT_NAME} SHARED ${SOURCE})
else ()
    add_library(${PROJECT_NAME} STATIC ${SOURCE})
endif ()
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_compile_options(${PROJECT_NAME} PRIVATE
        -Wall
        -Werror
        -Wextra
        -Wpedantic
        -Weffc++
        -Wold-style-cast
        -Wconversion
        -Wctor-dtor-privacy
        -Woverloaded-virtual
        -Wno-sign-conversion
        -Wno-unused-parameter
        -Wno-uninitialized
)

if (EXCHANGE_BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif ()

if (EXCHANGE_BUILD_EXAMPLE)
    add_subdirectory(example)
endif ()
