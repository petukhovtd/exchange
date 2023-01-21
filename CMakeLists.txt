cmake_minimum_required(VERSION 2.4)
project(exchange)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 17)

set(SOURCE
          src/exchange.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCE})
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
