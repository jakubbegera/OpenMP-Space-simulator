cmake_minimum_required(VERSION 3.5.2)
project(space)
project(generator)

# serial
#set(CMAKE_CXX_STANDARD 11)

# paraler
set(GCC_COVERAGE_COMPILE_FLAGS "-fopenmp -fopt-info-vec -std=c++11 -march=native -Ofast")
add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )


add_executable(space main.cpp MassPoint.cpp MassPoint.h SpaceSimulator.cpp SpaceSimulator.h GifBuilder.cpp GifBuilder.h
        gif.cpp gif.h settings.h)
add_executable(generator generator.cpp)