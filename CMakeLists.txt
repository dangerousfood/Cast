cmake_minimum_required(VERSION 3.7)
project(cast_advanced)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        3DBenchy.stl
        Header.h
        main.cpp
        Model.h
        ModelHelper.h
        Polygon.h
        Vertex.h)

add_executable(cast_advanced ${SOURCE_FILES})