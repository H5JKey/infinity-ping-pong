cmake_minimum_required(VERSION 3.10)
project(Program)

find_package(SFML 2.6 COMPONENTS
graphics window system REQUIRED)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/Ball.cpp
    src/Bot.cpp
    src/Bot.h
    src/Platform.h
    src/Player.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
)

if (WIN32)
    add_custom_command(TARGET $ {PROJECT_NAME} OST_BUILD 
        COMMAND ${CMAKE_COMMAND} 
    -E copy_directory "${SFML_DIR}/bin"
    $<TARGET_FILE_DIR:${PROJECT_NAME}>
)
endif()