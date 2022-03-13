cmake_minimum_required(VERSION 2.4)

project(exchange)

set(CMAKE_CXX_STANDARD 17)

add_compile_options( -Wall )
add_compile_options( -Werror )
add_compile_options( -Wextra )
add_compile_options( -Wpedantic )
add_compile_options( -Weffc++ )
add_compile_options( -Wold-style-cast )
add_compile_options( -Wconversion )
add_compile_options( -Wctor-dtor-privacy )
add_compile_options( -Woverloaded-virtual )
add_compile_options( -Wno-sign-conversion )
add_compile_options( -Wno-unused-parameter )
add_compile_options( -Wno-uninitialized )

include_directories(include)

set(SOURCE
          src/exchange.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCE})