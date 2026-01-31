cmake_minimum_required(VERSION 3.27)
project(GaleShapley)

set(CMAKE_CXX_STANDARD 17)

add_executable(GaleShapley src/main.cpp
        src/Node.cpp
        src/Node.h
        src/Matcher.cpp
        src/Matcher.h
        src/Verifier.cpp
        src/Verifier.h
        src/utilities.cpp
        src/utilities.h)
