cmake_minimum_required(VERSION 3.0)

project(IvyGenCore)

set(SOURCES
    basic_mesh.h
    basic_mesh.cpp
    ivy.h
    ivy.cpp
    vector2d.h
    vector3d.h
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})
