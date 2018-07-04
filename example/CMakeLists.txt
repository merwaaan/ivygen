cmake_minimum_required(VERSION 3.0)

project(IvyGenExample)

set(SOURCES
    main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/core
)

target_link_libraries(${PROJECT_NAME}
    IvyGenCore
)
