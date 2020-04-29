cmake_minimum_required(VERSION 3.9)

project(NEAT-BT)
set (CMAKE_CXX_STANDARD 17)

include_directories(".")

file(GLOB helloworld_SRC
    "*.h"
    "*.cpp"
)

add_executable(helloworld ${helloworld_SRC})

install(TARGETS ${helloworld_SRC} DESTINATION bin)