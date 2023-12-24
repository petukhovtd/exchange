project(test)

set(SRC
        common/test_message.cpp
        common/test_actor.cpp
        common/timer.cpp
        test_speed.cpp
)

add_executable(${PROJECT_NAME}_speed ${SRC})
target_link_libraries(${PROJECT_NAME}_speed exchange)

add_executable(${PROJECT_NAME}_template test_template.cpp)
target_link_libraries(${PROJECT_NAME}_template exchange)
