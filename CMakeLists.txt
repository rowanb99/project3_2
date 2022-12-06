cmake_minimum_required(VERSION 3.24)
project(project3_2)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES
        *.h
        *.cpp
        )

add_executable(project3_2 ${SOURCES} DataBase.cpp Header.cpp Relation.cpp)
