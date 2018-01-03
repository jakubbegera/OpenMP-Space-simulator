cmake_minimum_required(VERSION 3.5.2)
project(space)
project(generator)

set(CMAKE_CXX_STANDARD 11)

add_executable(space main.cpp MassPoint.cpp MassPoint.h SpaceSimulator.cpp SpaceSimulator.h GifBuilder.cpp GifBuilder.h
        gif.cpp gif.h settings.h)
add_executable(generator generator.cpp)