cmake_minimum_required(VERSION 3.9)

project(NEAT-BT)
set (CMAKE_CXX_STANDARD 17)

include_directories(".")

add_executable(${PROJECT_NAME}
    "Main.cpp"
)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)