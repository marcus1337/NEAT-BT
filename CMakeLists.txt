cmake_minimum_required(VERSION 3.9)

project(NEAT-BT)
set (CMAKE_CXX_STANDARD 17)

include_directories(".")

add_subdirectory(lib/Catch2/)
add_executable(${PROJECT_NAME}
    "Main.cpp"
    "Breeder.cpp"
    "Breeder.h"
	"Coordinator.cpp"
    "Coordinator.h"
	"Culler.cpp"
    "Culler.h"
	"Evolver.cpp"
    "Evolver.h"
	"GenerationInfo.cpp"
    "GenerationInfo.h"
	"IOHandler.cpp"
    "IOHandler.h"
	"Mutate.cpp"
    "Mutate.h"
	"Node.cpp"
    "Node.h"
	"Speciator.cpp"
    "Speciator.h"
	"Specie.cpp"
    "Specie.h"
	"Tree.cpp"
    "Tree.h"
	"TreeIterator.cpp"
    "TreeIterator.h"
	"Utils.cpp"
    "Utils.h"
)

#install(TARGETS ${PROJECT_NAME} DESTINATION bin)

target_link_libraries(${PROJECT_NAME} Catch2::Catch2)
include(CTest)
include(Catch)
catch_discover_tests(${PROJECT_NAME})