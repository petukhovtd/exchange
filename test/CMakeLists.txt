project(exchange-test LANGUAGES CXX)

message(STATUS "Build ${PROJECT_NAME}")

add_executable(${PROJECT_NAME}
        test_exchange.cpp
        test_actor_helper.cpp
)
target_link_libraries(${PROJECT_NAME} exchange gtest gtest_main)
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})


add_executable(${PROJECT_NAME}-speed
        common/timer.cpp
        test_speed.cpp
)
target_link_libraries(${PROJECT_NAME}-speed exchange gtest gtest_main)
